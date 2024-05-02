#pragma once
#include <cassert>

#include "v6502/cpu.h"

#define TEST void test(CPU *cpu)
#define STATUS_ASSERT(statusFlags)                                             \
  assert(cpu->status ==                                                        \
         (STATUS_INTERRUPT_DISABLE | STATUS_UNUSED | statusFlags))
