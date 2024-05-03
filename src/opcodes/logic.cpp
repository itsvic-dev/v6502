#include "v6502/cpu.h"
#include "v6502/opcodes.h"
#include <cstdint>

OPCODE(_and) {
  cpu->a = cpu->a & (cpu->fetchByteWithMode(mode));
  cpu->evaluateFlags(cpu->a);
}

OPCODE(bit) {
  uint8_t m = cpu->fetchByteWithMode(mode);
  uint8_t result = cpu->a & m;
  cpu->status = (cpu->status & ~(0b11 << 6)) | (m & (0b11 << 6));
  cpu->clearFlags(STATUS_ZERO);
  if (result == 0) {
    cpu->setFlags(STATUS_ZERO);
  }
}

OPCODE(eor) {
  cpu->a = cpu->a ^ (cpu->fetchByteWithMode(mode));
  cpu->evaluateFlags(cpu->a);
}

OPCODE(ora) {
  cpu->a = cpu->a | (cpu->fetchByteWithMode(mode));
  cpu->evaluateFlags(cpu->a);
}
