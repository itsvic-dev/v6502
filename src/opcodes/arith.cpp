#include "v6502/cpu.h"
#include "v6502/opcodes.h"

OPCODE(cmp) {
  uint8_t mem = cpu->fetchByteWithMode(mode);
  uint8_t result = cpu->a - mem;
  cpu->clearFlags(STATUS_NEGATIVE | STATUS_ZERO | STATUS_CARRY);
  cpu->evaluateFlags(result);
  if (cpu->a > mem) {
    cpu->setFlags(STATUS_CARRY);
  }
}

OPCODE(cpx) {
  uint8_t mem = cpu->fetchByteWithMode(mode);
  uint8_t result = cpu->x - mem;
  cpu->clearFlags(STATUS_NEGATIVE | STATUS_ZERO | STATUS_CARRY);
  cpu->evaluateFlags(result);
  if (cpu->x > mem) {
    cpu->setFlags(STATUS_CARRY);
  }
}

OPCODE(cpy) {
  uint8_t mem = cpu->fetchByteWithMode(mode);
  uint8_t result = cpu->y - mem;
  cpu->clearFlags(STATUS_NEGATIVE | STATUS_ZERO | STATUS_CARRY);
  cpu->evaluateFlags(result);
  if (cpu->y > mem) {
    cpu->setFlags(STATUS_CARRY);
  }
}
