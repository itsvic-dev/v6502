#include "v6502/cpu.h"
#include "v6502/modes.h"
#include "v6502/opcodes.h"

OPCODE(asl) {
  bool newCarry = false;
  if (mode == ACCUMULATOR) {
    newCarry = (cpu->a & (1 << 7)) != 0;
    cpu->a = cpu->a << 1;
  } else {
    uint16_t effectiveAddr = cpu->fetchEffectiveModeValue(mode);
    uint8_t value = cpu->bus->read(effectiveAddr);
    newCarry = (value & (1 << 7)) != 0;
    cpu->bus->write(effectiveAddr, value << 1);
  }

  cpu->clearFlags(STATUS_CARRY);
  if (newCarry) {
    cpu->setFlags(STATUS_CARRY);
  }
}
