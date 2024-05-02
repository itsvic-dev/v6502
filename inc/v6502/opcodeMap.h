#pragma once

#include "v6502/cpu.h"
#include "v6502/modes.h"
#include <map>
#include <string>

typedef void (*OpcodeFunction)(CPU *, AddressingMode);

struct Opcode {
  const std::string basicInfo;
  const OpcodeFunction function = nullptr;
  // Instructions often have a common core but with different addressing modes.
  const AddressingMode mode = IMPLIED;
};

extern std::map<uint8_t, Opcode> cpuOpcodes;
