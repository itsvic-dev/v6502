#include "testMain.h"
#include "v6502/cpu.h"

TEST {
  cpu->a = 0x7F;

  // SBC #$FE
  cpu->bus->write(0, 0xE9);
  cpu->bus->write(1, 0xFE);
  cpu->reset();
  cpu->executeStep();

  assert(cpu->a == 0x80);
  assert(FLAG_IS_SET(cpu->status, STATUS_NEGATIVE));
  assert(FLAG_IS_SET(cpu->status, STATUS_OVERFLOW));
  assert(FLAG_IS_CLEAR(cpu->status, STATUS_ZERO));
  assert(FLAG_IS_CLEAR(cpu->status, STATUS_CARRY));
}
