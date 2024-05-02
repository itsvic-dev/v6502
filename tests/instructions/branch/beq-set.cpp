#include "testMain.h"
#include "v6502/cpu.h"
#include <cassert>

TEST {
  // BEQ $0012
  cpu->bus->write(0, 0xF0);
  cpu->bus->write(1, 0x10);

  cpu->reset();

  // make sure its set
  cpu->setFlags(STATUS_ZERO);
  cpu->executeStep();

  assert(cpu->pc == 0x0012);
}
