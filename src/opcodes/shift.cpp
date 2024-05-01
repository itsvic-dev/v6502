#include "v6502/cpu.h"
#include "v6502/modes.h"
#include "v6502/opcodes.h"

OPCODE(asl) {
  bool newCarry = false;
  if (mode == ACCUMULATOR) {
    newCarry = (cpu->a & (1 << 7)) != 0;
    cpu->a = cpu->a << 1;
    cpu->evaluateFlags(cpu->a);
  } else {
    uint16_t effectiveAddr = cpu->fetchEffectiveModeValue(mode);
    uint8_t value = cpu->bus->read(effectiveAddr);
    newCarry = (value & (1 << 7)) != 0;
    value = value << 1;
    cpu->bus->write(effectiveAddr, value);
    cpu->evaluateFlags(value);
  }

  cpu->clearFlags(STATUS_CARRY);
  if (newCarry) {
    cpu->setFlags(STATUS_CARRY);
  }
}

OPCODE(lsr) {
  bool newCarry = false;
  if (mode == ACCUMULATOR) {
    newCarry = (cpu->a & 1) != 0;
    cpu->a = cpu->a >> 1;
    cpu->evaluateFlags(cpu->a);
  } else {
    uint16_t effectiveAddr = cpu->fetchEffectiveModeValue(mode);
    uint8_t value = cpu->bus->read(effectiveAddr);
    newCarry = (value & 1) != 0;
    value = value >> 1;
    cpu->bus->write(effectiveAddr, value);
    cpu->evaluateFlags(value);
  }

  cpu->clearFlags(STATUS_CARRY);
  if (newCarry) {
    cpu->setFlags(STATUS_CARRY);
  }
}

OPCODE(rol) {
  bool oldCarry = FLAG_IS_SET(cpu->status, STATUS_CARRY);
  bool newCarry = false;
  if (mode == ACCUMULATOR) {
    newCarry = (cpu->a & (1 << 7)) != 0;
    cpu->a = (cpu->a << 1) | oldCarry;
    cpu->evaluateFlags(cpu->a);
  } else {
    uint16_t effectiveAddr = cpu->fetchEffectiveModeValue(mode);
    uint8_t value = cpu->bus->read(effectiveAddr);
    newCarry = (value & (1 << 7)) != 0;
    value = (value << 1) | oldCarry;
    cpu->bus->write(effectiveAddr, value);
    cpu->evaluateFlags(value);
  }

  cpu->clearFlags(STATUS_CARRY);
  if (newCarry) {
    cpu->setFlags(STATUS_CARRY);
  }
}

OPCODE(ror) {
  bool oldCarry = FLAG_IS_SET(cpu->status, STATUS_CARRY);
  bool newCarry = false;
  if (mode == ACCUMULATOR) {
    newCarry = (cpu->a & 1) != 0;
    cpu->a = (cpu->a >> 1) | (oldCarry << 7);
    cpu->evaluateFlags(cpu->a);
  } else {
    uint16_t effectiveAddr = cpu->fetchEffectiveModeValue(mode);
    uint8_t value = cpu->bus->read(effectiveAddr);
    newCarry = (value & 1) != 0;
    value = (value >> 1) | (oldCarry << 7);
    cpu->bus->write(effectiveAddr, value);
    cpu->evaluateFlags(value);
  }

  cpu->clearFlags(STATUS_CARRY);
  if (newCarry) {
    cpu->setFlags(STATUS_CARRY);
  }
}
