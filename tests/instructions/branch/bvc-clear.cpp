#include "testMain.h"
#include "v6502/cpu.h"
#include <cassert>

TEST {
  // BVC $0012
  cpu->bus->write(0, 0x50);
  cpu->bus->write(1, 0x10);

  cpu->reset();

  cpu->clearFlags(STATUS_OVERFLOW);
  cpu->executeStep();

  assert(cpu->pc == 0x0012);
}
