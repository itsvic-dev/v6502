#pragma once

#include "cpu/cpu.h"
#include <cstdint>
#include <functional>
#include <map>
#include <string>

struct Opcode {
  const std::string basicInfo;
  const std::function<void(CPU *)> function;
};

extern std::map<uint8_t, Opcode> cpuOpcodes;
