#include "cpu/cpu.h"
#include "cpu/opcodes.h"

OPCODE(_and) {
  cpu->a = cpu->a & (cpu->fetchByteWithMode(mode));
  cpu->evaluateFlags(cpu->a);
}

OPCODE(bit) {
  uint8_t result = cpu->a & (cpu->fetchByteWithMode(mode));
  const uint8_t mask = (1 << 7) | (1 << 6);
  cpu->status = (result & mask) | (cpu->status & ~mask);
  cpu->clearFlags(STATUS_ZERO);
  if (result == 0) {
    cpu->setFlags(STATUS_ZERO);
  }
}

OPCODE(eor) {
  cpu->a = cpu->a ^ (cpu->fetchByteWithMode(mode));
  cpu->evaluateFlags(cpu->a);
}

OPCODE(ora) {
  cpu->a = cpu->a | (cpu->fetchByteWithMode(mode));
  cpu->evaluateFlags(cpu->a);
}
