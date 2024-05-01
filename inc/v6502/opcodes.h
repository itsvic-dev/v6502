#pragma once

#include "v6502/cpu.h"
#include "v6502/modes.h"
#include <cstdint>
#include <functional>
#include <map>
#include <string>

struct Opcode {
  const std::string basicInfo;
  const std::function<void(CPU *, AddressingMode)> function;
  // Instructions often have a common core but with different addressing modes.
  const AddressingMode mode = IMPLIED;
};

#define OPCODE(name) void name(CPU *cpu, AddressingMode mode)

extern std::map<uint8_t, Opcode> cpuOpcodes;
