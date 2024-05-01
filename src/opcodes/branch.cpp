#include "v6502/cpu.h"
#include "v6502/opcodes.h"

OPCODE(bcc) {
  uint16_t addr = cpu->fetchEffectiveModeValue(mode);
  if (FLAG_IS_CLEAR(cpu->status, STATUS_CARRY))
    cpu->pc = addr;
}

OPCODE(bcs) {
  uint16_t addr = cpu->fetchEffectiveModeValue(mode);
  if (FLAG_IS_SET(cpu->status, STATUS_CARRY))
    cpu->pc = addr;
}

OPCODE(beq) {
  uint16_t addr = cpu->fetchEffectiveModeValue(mode);
  if (FLAG_IS_SET(cpu->status, STATUS_ZERO))
    cpu->pc = addr;
}

OPCODE(bmi) {
  uint16_t addr = cpu->fetchEffectiveModeValue(mode);
  if (FLAG_IS_SET(cpu->status, STATUS_NEGATIVE))
    cpu->pc = addr;
}

OPCODE(bne) {
  uint16_t addr = cpu->fetchEffectiveModeValue(mode);
  if (FLAG_IS_CLEAR(cpu->status, STATUS_ZERO))
    cpu->pc = addr;
}

OPCODE(bpl) {
  uint16_t addr = cpu->fetchEffectiveModeValue(mode);
  if (FLAG_IS_CLEAR(cpu->status, STATUS_NEGATIVE))
    cpu->pc = addr;
}

OPCODE(bvc) {
  uint16_t addr = cpu->fetchEffectiveModeValue(mode);
  if (!FLAG_IS_SET(cpu->status, STATUS_OVERFLOW))
    cpu->pc = addr;
}

OPCODE(bvs) {
  uint16_t addr = cpu->fetchEffectiveModeValue(mode);
  if (FLAG_IS_SET(cpu->status, STATUS_OVERFLOW))
    cpu->pc = addr;
}
