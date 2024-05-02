// does ADC #$01 work properly with A=0x7F?
#include "testMain.h"
#include "v6502/cpu.h"

TEST {
  cpu->a = 0x7F;

  cpu->bus->write(0, 0x69); // nice
  cpu->bus->write(1, 0x01);
  cpu->reset();
  cpu->executeStep();

  assert(cpu->a == 0x80);
  STATUS_ASSERT(STATUS_NEGATIVE | STATUS_OVERFLOW);
}
