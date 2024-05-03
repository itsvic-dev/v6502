// does ADC #$01 work properly with A=0xFF?
#include "testMain.h"
#include "v6502/cpu.h"
#include <cassert>

TEST {
  cpu->bus->write(0, 0x69); // nice
  cpu->bus->write(1, 0x80);
  cpu->reset();
  cpu->executeStep();

  assert(cpu->a == 0x80);
  assert(FLAG_IS_SET(cpu->status, STATUS_NEGATIVE));
  assert(FLAG_IS_CLEAR(cpu->status, STATUS_OVERFLOW));
  assert(FLAG_IS_CLEAR(cpu->status, STATUS_ZERO));
  assert(FLAG_IS_CLEAR(cpu->status, STATUS_CARRY));
}
