#pragma once
#include <cassert>

#include "v6502/cpu.h"

#define TEST void test(CPU *cpu)
#define DEFAULT_FLAGS                                                          \
  (STATUS_BREAK_COMMAND | STATUS_INTERRUPT_DISABLE | STATUS_UNUSED)
#define STATUS_ASSERT(statusFlags)                                             \
  assert(cpu->status == (DEFAULT_FLAGS | statusFlags))
