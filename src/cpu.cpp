#include "v6502/cpu.h"
#include "v6502/memory.h"
#include "v6502/modes.h"
#include "v6502/opcodeMap.h"
#include "v6502/print.h"

CPU::CPU(MemoryBus *bus) : bus(bus) {}

uint16_t CPU::readWord(uint16_t addr, bool crossPage) {
  uint16_t highAddr = addr + 1;
  if (!crossPage) {
    highAddr = (highAddr & 0xff) | (addr & 0xff00);
  }
  return bus->read(addr) | ((uint16_t)bus->read(highAddr) << 8);
}

uint8_t CPU::fetchByte() { return bus->read(pc++); }
uint16_t CPU::fetchWord() { return fetchByte() | ((uint16_t)fetchByte() << 8); }

uint8_t CPU::fetchByteWithMode(AddressingMode mode) {
  switch (mode) {
  case ACCUMULATOR:
    return a;
  case IMMEDIATE:
    return fetchByte();
  case ABSOLUTE:
    return bus->read(fetchWord());
  case X_ABSOLUTE:
    return bus->read(fetchWord() + x);
  case Y_ABSOLUTE:
    return bus->read(fetchWord() + y);
  case ZERO_PAGE:
    return bus->read(fetchByte());
  case X_ZERO_PAGE:
    return bus->read(fetchByte() + x);
  case Y_ZERO_PAGE:
    return bus->read(fetchByte() + y);
  case X_ZP_INDIRECT:
    return bus->read(readWord(fetchByte() + x));
  case ZP_INDIRECT_Y:
    return bus->read(readWord(fetchByte()) + y);
  default:
    throw "invalid mode passed to fetchByteWithMode";
  }
}

uint16_t CPU::fetchEffectiveModeValue(AddressingMode mode) {
  switch (mode) {
  case IMMEDIATE:
    return fetchByte();
  case ABSOLUTE:
    return fetchWord();
  case X_ABSOLUTE:
    return fetchWord() + x;
  case Y_ABSOLUTE:
    return fetchWord() + y;
  case ABSOLUTE_INDIRECT:
    return readWord(fetchWord(), false);
  case ZERO_PAGE:
    return fetchByte();
  case X_ZERO_PAGE:
    return fetchByte() + x;
  case Y_ZERO_PAGE:
    return fetchByte() + y;
  case X_ZP_INDIRECT:
    return readWord(fetchByte() + x);
  case ZP_INDIRECT_Y:
    return readWord(fetchByte()) + y;
  case RELATIVE: {
    int8_t offset = fetchByte();
    // PC now points at the next instruction, apply the offset to PC
    return pc + offset;
  }
  default:
    throw "invalid mode passed to fetchByteWithMode";
  }
}

void CPU::setFlags(uint8_t flags) { status |= flags; }
void CPU::clearFlags(uint8_t flags) { status &= ~flags; }

void CPU::evaluateFlags(uint8_t value) {
  clearFlags(STATUS_ZERO | STATUS_NEGATIVE);

  if (value == 0)
    setFlags(STATUS_ZERO);

  if ((value & 0x80) != 0) {
    setFlags(STATUS_NEGATIVE);
  }
}

void CPU::pushStack(uint8_t data) { bus->write(0x100 + sp--, data); }
uint8_t CPU::popStack() { return bus->read(0x100 + ++sp); }

void CPU::reset() {
  // CPU does 3 fake writes to the stack during reset
  sp -= 3;
  setFlags(STATUS_INTERRUPT_DISABLE);
  this->pc = readWord(0xFFFC);
}

#ifdef V6502_DEBUG
static uint16_t getDisasmOperand(CPU *cpu, AddressingMode mode) {
  switch (mode) {
  case IMMEDIATE:
  case ZERO_PAGE:
  case X_ZERO_PAGE:
  case Y_ZERO_PAGE:
  case X_ZP_INDIRECT:
  case ZP_INDIRECT_Y:
    return cpu->bus->read(cpu->pc);
  case ABSOLUTE:
  case X_ABSOLUTE:
  case Y_ABSOLUTE:
  case ABSOLUTE_INDIRECT:
    return cpu->readWord(cpu->pc);
  case RELATIVE:
    return cpu->pc + 2 + (int8_t)(cpu->readWord(cpu->pc));
  default:
    return 0;
  }
}
#endif

void CPU::executeStep() {
  uint8_t opcode = fetchByte();
  if (!cpuOpcodes.contains(opcode)) {
    print_err("[v6502] unknown CPU opcode encountered: {:02x}\n", opcode);
    throw 1;
  }
  auto instruction = cpuOpcodes[opcode];
#ifdef V6502_DEBUG
  char disasmInstruction[256] = {0};
  snprintf(disasmInstruction, 256, instruction.basicInfo.c_str(),
           getDisasmOperand(this, instruction.mode));
#endif
  instruction.function(this, instruction.mode);
#ifdef V6502_DEBUG
  print_err(
      "{: <16}  A:{:02x}  X:{:02x}  Y:{:02x}  P:{:02x}  SP:{:02x}  PC:{:04x}\n",
      disasmInstruction, a, x, y, status, sp, pc);
#endif
}
