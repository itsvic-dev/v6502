#include "v6502/opcodes.h"

// $EA and variants
OPCODE(nop_implied) {
  (void)cpu;
  (void)mode;
}

// $80 etc
OPCODE(nop_mode) { cpu->fetchByteWithMode(mode); }
