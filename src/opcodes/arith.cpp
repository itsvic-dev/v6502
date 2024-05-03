#include "v6502/cpu.h"
#include "v6502/internal.h"
#include "v6502/opcodes.h"

OPCODE(adc) {
  if (FLAG_IS_SET(cpu->status, STATUS_DECIMAL)) {
    v6502Internal::logWarning("ADC: decimal mode is not supported yet");
  }
  uint8_t m = cpu->fetchByteWithMode(mode);
  int16_t result = cpu->a + m + FLAG_IS_SET(cpu->status, STATUS_CARRY);

  cpu->clearFlags(STATUS_CARRY | STATUS_OVERFLOW);
  if (result > 0xff) {
    cpu->setFlags(STATUS_CARRY);
  }
  if ((m ^ result) & (cpu->a ^ result) & 0x80) {
    cpu->setFlags(STATUS_OVERFLOW);
  }

  cpu->a = result & 0xFF;
  cpu->evaluateFlags(cpu->a);
}

OPCODE(cmp) {
  uint8_t mem = cpu->fetchByteWithMode(mode);
  uint8_t result = cpu->a - mem;
  cpu->clearFlags(STATUS_NEGATIVE | STATUS_ZERO | STATUS_CARRY);
  cpu->evaluateFlags(result);
  if (cpu->a >= mem) {
    cpu->setFlags(STATUS_CARRY);
  }
}

OPCODE(cpx) {
  uint8_t mem = cpu->fetchByteWithMode(mode);
  uint8_t result = cpu->x - mem;
  cpu->clearFlags(STATUS_NEGATIVE | STATUS_ZERO | STATUS_CARRY);
  cpu->evaluateFlags(result);
  if (cpu->x >= mem) {
    cpu->setFlags(STATUS_CARRY);
  }
}

OPCODE(cpy) {
  uint8_t mem = cpu->fetchByteWithMode(mode);
  uint8_t result = cpu->y - mem;
  cpu->clearFlags(STATUS_NEGATIVE | STATUS_ZERO | STATUS_CARRY);
  cpu->evaluateFlags(result);
  if (cpu->y >= mem) {
    cpu->setFlags(STATUS_CARRY);
  }
}

OPCODE(sbc) {
  if (FLAG_IS_SET(cpu->status, STATUS_DECIMAL)) {
    v6502Internal::logWarning("SBC: decimal mode is not supported yet");
  }
  uint8_t m = cpu->fetchByteWithMode(mode);
  int16_t result = cpu->a - m - !FLAG_IS_SET(cpu->status, STATUS_CARRY);

  cpu->clearFlags(STATUS_CARRY | STATUS_OVERFLOW);
  if (result >= 0) {
    cpu->setFlags(STATUS_CARRY);
  }
  if ((~m ^ result) & (cpu->a ^ result) & 0x80) {
    cpu->setFlags(STATUS_OVERFLOW);
  }

  cpu->a = result & 0xFF;
  cpu->evaluateFlags(cpu->a);
}
