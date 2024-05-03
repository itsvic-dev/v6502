#pragma once

#include "v6502/memory.h"
#include "v6502/modes.h"
#include <cstdint>

#define STATUS_CARRY (1 << 0)
#define STATUS_ZERO (1 << 1)
#define STATUS_INTERRUPT_DISABLE (1 << 2)
#define STATUS_DECIMAL (1 << 3)
#define STATUS_BREAK_COMMAND (1 << 4)
#define STATUS_UNUSED (1 << 5)
#define STATUS_OVERFLOW (1 << 6)
#define STATUS_NEGATIVE (1 << 7)

// UNUSED is hard-wired to be set
#define FLAG_IS_SET(status, flag)                                              \
  (flag == STATUS_UNUSED ? 1 : (status & flag) == flag)
#define FLAG_IS_CLEAR(status, flag)                                            \
  (flag == STATUS_UNUSED ? 0 : (status & flag) == 0)

class CPU {
public:
  CPU(MemoryBus *bus);

  void reset();
  void executeStep();

  uint16_t pc = 0;
  uint8_t a = 0;
  uint8_t x = 0;
  uint8_t y = 0;
  uint8_t status = STATUS_UNUSED; // UNUSED is hard-wired to be set
  uint8_t sp = 0;

  MemoryBus *bus;

  void setFlags(uint8_t flags);
  void clearFlags(uint8_t flags);
  void evaluateFlags(uint8_t value);

  void pushStack(uint8_t data);
  uint8_t popStack();

  uint16_t readWord(uint16_t addr, bool crossPage = true);
  uint8_t fetchByte();
  uint16_t fetchWord();

  uint8_t fetchByteWithMode(AddressingMode mode);
  uint16_t fetchEffectiveModeValue(AddressingMode mode);
};
