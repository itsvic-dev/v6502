#include "testMain.h"
#include "v6502/cpu.h"
#include <cassert>

TEST {
  // SBC #$01
  cpu->bus->write(0, 0xE9);
  cpu->bus->write(1, 0x01);
  cpu->reset();
  cpu->executeStep();

  assert(cpu->a == 0xFE);
  assert(FLAG_IS_SET(cpu->status, STATUS_NEGATIVE));
  assert(FLAG_IS_CLEAR(cpu->status, STATUS_OVERFLOW));
  assert(FLAG_IS_CLEAR(cpu->status, STATUS_ZERO));
  assert(FLAG_IS_CLEAR(cpu->status, STATUS_CARRY));
}
