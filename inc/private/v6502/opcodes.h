#pragma once

#include "v6502/cpu.h"
#include "v6502/modes.h"

#define OPCODE(name) void name(CPU *cpu, AddressingMode mode)
