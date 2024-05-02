#include "testMain.h"
#include "v6502/cpu.h"
#include <cassert>

TEST {
  // BCC $0012
  cpu->bus->write(0, 0x90);
  cpu->bus->write(1, 0x10);

  cpu->reset();

  // make sure its cleared
  cpu->clearFlags(STATUS_CARRY);
  cpu->executeStep();

  assert(cpu->pc == 0x0012);
}
