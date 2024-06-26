#include "v6502/opcodes.h"
#include <cstdint>

OPCODE(brk) {
  (void)mode;
  uint16_t nextPc = cpu->pc + 1;
  cpu->pushStack((nextPc >> 8) & 0xff);
  cpu->pushStack(nextPc & 0xff);
  cpu->pushStack(cpu->status);
  cpu->pc = cpu->readWord(0xFFFE);
  cpu->setFlags(STATUS_INTERRUPT_DISABLE | STATUS_BREAK_COMMAND);
}

OPCODE(jmp) { cpu->pc = cpu->fetchEffectiveModeValue(mode); }

OPCODE(jsr) {
  uint16_t effectiveAddress = cpu->fetchEffectiveModeValue(mode);
  uint16_t pointingPc = cpu->pc - 1;
  cpu->pushStack((pointingPc >> 8) & 0xff);
  cpu->pushStack(pointingPc & 0xff);
  cpu->pc = effectiveAddress;
}

OPCODE(rti) {
  (void)mode;
  uint8_t mask = ~(STATUS_UNUSED | STATUS_BREAK_COMMAND);
  cpu->status = (cpu->popStack() & mask) | (cpu->status & ~mask);
  uint8_t pcLow = cpu->popStack();
  uint8_t pcHigh = cpu->popStack();
  cpu->pc = (((uint16_t)pcHigh) << 8) | pcLow;
}

OPCODE(rts) {
  (void)mode;
  uint8_t pcLow = cpu->popStack();
  uint8_t pcHigh = cpu->popStack();
  cpu->pc = ((((uint16_t)pcHigh) << 8) | pcLow) + 1;
}
