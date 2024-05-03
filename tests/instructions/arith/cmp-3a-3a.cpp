#include "testMain.h"

TEST {
  cpu->a = 0x3A;
  // CMP #$3A
  cpu->bus->write(0, 0xC9);
  cpu->bus->write(1, 0x3A);
  cpu->reset();
  cpu->executeStep();
  STATUS_ASSERT(STATUS_ZERO | STATUS_CARRY);
}
