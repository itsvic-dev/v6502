#include "v6502/opcodes.h"

OPCODE(dec) {
  uint16_t mem = cpu->fetchEffectiveModeValue(mode);
  uint8_t res = cpu->bus->read(mem) - 1;
  cpu->bus->write(mem, res);
  cpu->evaluateFlags(res);
}

OPCODE(dex) {
  (void)mode;
  cpu->evaluateFlags(--cpu->x);
}

OPCODE(dey) {
  (void)mode;
  cpu->evaluateFlags(--cpu->y);
}

OPCODE(inc) {
  uint16_t mem = cpu->fetchEffectiveModeValue(mode);
  uint8_t res = cpu->bus->read(mem) + 1;
  cpu->bus->write(mem, res);
  cpu->evaluateFlags(res);
}

OPCODE(inx) {
  (void)mode;
  cpu->evaluateFlags(++cpu->x);
}

OPCODE(iny) {
  (void)mode;
  cpu->evaluateFlags(++cpu->y);
}
