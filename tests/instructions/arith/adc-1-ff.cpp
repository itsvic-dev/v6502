// does ADC #$01 work properly with A=0xFF?
#include "testMain.h"
#include "v6502/cpu.h"

TEST {
  cpu->a = 0xFF;

  cpu->bus->write(0, 0x69); // nice
  cpu->bus->write(1, 0x01);
  cpu->reset();
  cpu->executeStep();

  assert(cpu->a == 0);
  STATUS_ASSERT(STATUS_ZERO | STATUS_CARRY);
}
