#include "cpu/cpu.h"
#include "cpu/memory.h"
#include <cstdint>

CPU::CPU(MemoryBus *bus) : bus(bus) {}

uint16_t CPU::readWord(uint16_t addr) {
  return bus->read(addr) | ((uint16_t)bus->read(addr + 1) << 8);
}

void CPU::setFlags(uint8_t flags) { status |= flags; }
void CPU::clearFlags(uint8_t flags) { status ^= flags; }

void CPU::pushStack(uint8_t data) { bus->write(0x100 + sp--, data); }
uint8_t CPU::popStack() { return bus->read(0x100 + sp++); }

void CPU::reset() {
  // CPU does 3 fake writes to the stack during reset
  sp -= 3;
  setFlags(STATUS_INTERRUPT_DISABLE);
  this->pc = readWord(0xFFFC);
}
