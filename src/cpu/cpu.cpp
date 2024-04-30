#include "cpu/cpu.h"
#include "cpu/memory.h"
#include "cpu/opcodes.h"
#include "vprint.h"
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
uint8_t CPU::popStack() { return bus->read(0x100 + sp++); }

void CPU::reset() {
  // CPU does 3 fake writes to the stack during reset
  sp -= 3;
  setFlags(STATUS_INTERRUPT_DISABLE);
  this->pc = readWord(0xFFFC);
}

void CPU::executeStep() {
#ifdef V6502_DEBUG
  print("---\nPC: ${:04x}\tSP: ${:02x}\nA:  ${:02x}\t\tP:  ${:02x}\nX:  "
        "${:02x}\t\tY:  "
        "${:02x}\n",
        pc, sp, a, status, x, y);
#endif

  uint8_t opcode = fetchByte();
  if (!cpuOpcodes.contains(opcode)) {
    print("[v6502] unknown CPU opcode encountered: {:02x}\n", opcode);
    std::terminate();
  }
  auto instruction = cpuOpcodes[opcode];
  print("\n{}\n", instruction.basicInfo);
  instruction.function(this, instruction.mode);
}
