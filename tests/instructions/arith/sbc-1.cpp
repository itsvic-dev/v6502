#include "testMain.h"
#include "v6502/cpu.h"

TEST {
  // SBC #$01
  cpu->bus->write(0, 0xE9);
  cpu->bus->write(1, 0x01);
  cpu->reset();
  cpu->executeStep();

  assert(cpu->a == 0xFE);
  STATUS_ASSERT(STATUS_NEGATIVE);
}
