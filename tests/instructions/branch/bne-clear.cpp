#include "testMain.h"
#include "v6502/cpu.h"
#include <cassert>

TEST {
  // BNE $0012
  cpu->bus->write(0, 0xD0);
  cpu->bus->write(1, 0x10);

  cpu->reset();

  // make sure its cleared
  cpu->clearFlags(STATUS_ZERO);
  cpu->executeStep();

  assert(cpu->pc == 0x0012);
}
