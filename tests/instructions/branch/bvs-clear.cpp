#include "testMain.h"
#include "v6502/cpu.h"
#include <cassert>

TEST {
  // BVS $0012
  cpu->bus->write(0, 0x70);
  cpu->bus->write(1, 0x10);

  cpu->reset();

  cpu->clearFlags(STATUS_OVERFLOW);
  cpu->executeStep();

  assert(cpu->pc != 0x0012);
}
