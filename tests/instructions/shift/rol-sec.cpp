#include "testMain.h"
#include "v6502/cpu.h"
#include <cassert>

TEST {
  cpu->bus->write(0, 0x2A); // ROL A
  cpu->reset();
  cpu->setFlags(STATUS_CARRY);
  cpu->executeStep();

  assert(cpu->a == 1);
  STATUS_ASSERT(0);
}
