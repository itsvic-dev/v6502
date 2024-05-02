#include "testMain.h"
#include "v6502/cpu.h"
#include <cassert>

TEST {
  // BMI $0012
  cpu->bus->write(0, 0x30);
  cpu->bus->write(1, 0x10);

  cpu->reset();

  // make sure its cleared
  cpu->clearFlags(STATUS_NEGATIVE);
  cpu->executeStep();

  assert(cpu->pc != 0x0012);
}
