// does ADC #$01 work properly?
#include "testMain.h"
#include "v6502/cpu.h"

TEST {
  cpu->bus->write(0, 0x69); // nice
  cpu->bus->write(1, 0x01);
  cpu->reset();
  cpu->executeStep();

  assert(cpu->a == 0x01);
  STATUS_ASSERT(0); // no special status flags set
}
