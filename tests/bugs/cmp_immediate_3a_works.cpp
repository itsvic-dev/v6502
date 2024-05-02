#include "testMain.h"
#include <cassert>

TEST {
  cpu->a = 0x3A;
  // CMP #$3A
  cpu->bus->write(0, 0xC9);
  cpu->bus->write(1, 0x3A);
  cpu->reset();
  cpu->executeStep();
  assert(cpu->status == (STATUS_UNUSED | STATUS_INTERRUPT_DISABLE |
                         STATUS_ZERO | STATUS_CARRY));
}
