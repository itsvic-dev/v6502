#include "tests/cpuFixture.h"
#include "v6502/cpu.h"
#include "gtest/gtest.h"

TEST_F(V6502Test, IsCmp3ACorrect) {
  cpu.a = 0x3A;
  // CMP #$3A
  bus.write(0, 0xC9);
  bus.write(1, 0x3A);
  cpu.reset();
  cpu.executeStep();
  EXPECT_EQ(cpu.status, STATUS_UNUSED | STATUS_INTERRUPT_DISABLE | STATUS_ZERO |
                            STATUS_CARRY);
}
