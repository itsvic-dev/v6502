#include "v6502/cpu.h"
#include "v6502/memory.h"
#include "v6502/modes.h"
#include "v6502/opcodes.h"
#include "v6502/print.h"
#include <cstdint>
#include <exception>

CPU::CPU(MemoryBus *bus) : bus(bus) {}

uint16_t CPU::readWord(uint16_t addr) {
  return bus->read(addr) | ((uint16_t)bus->read(addr + 1) << 8);
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
  case ABSOLUTE_INDIRECT:
    return bus->read(readWord(fetchWord()));
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
  case ACCUMULATOR:
    return a;
  case IMMEDIATE:
    return fetchByte();
  case ABSOLUTE:
    return fetchWord();
  case X_ABSOLUTE:
    return fetchWord() + x;
  case Y_ABSOLUTE:
    return fetchWord() + y;
  case ABSOLUTE_INDIRECT:
    return readWord(fetchWord());
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

void CPU::executeStep() {
  uint8_t opcode = fetchByte();
  if (!cpuOpcodes.contains(opcode)) {
    print("[v6502] unknown CPU opcode encountered: {:02x}\n", opcode);
    std::terminate();
  }
  auto instruction = cpuOpcodes[opcode];
  instruction.function(this, instruction.mode);
#ifdef V6502_DEBUG
  print("{: <10}  A:{:02x}  X:{:02x}  Y:{:02x}  P:{:02x}  SP:{:02x}\n",
        instruction.basicInfo, a, x, y, status, sp);
#endif
}
