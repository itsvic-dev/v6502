#include "testMain.h"
#include "v6502/cpu.h"
#include <cassert>

TEST {
  cpu->a = 0x80;
  cpu->bus->write(0, 0x0a); // ASL A
  cpu->reset();
  cpu->executeStep();

  assert(cpu->a == 0);
  STATUS_ASSERT(STATUS_ZERO | STATUS_CARRY);
}
