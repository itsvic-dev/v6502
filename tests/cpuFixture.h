#pragma once

#include "v6502/cpu.h"
#include "v6502/memory.h"
#include "gtest/gtest.h"
#include <cstdint>

class SimpleRAMBus : public MemoryBus {
public:
  SimpleRAMBus();
  ~SimpleRAMBus();
  uint8_t read(uint16_t addr) override;
  void write(uint16_t addr, uint8_t data) override;

private:
  uint8_t *ram;
};

class V6502Test : public testing::Test {
protected:
  V6502Test();

  SimpleRAMBus bus;
  CPU cpu;
};
