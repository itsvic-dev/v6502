#include "v6502/cpu.h"
#include "v6502/opcodes.h"

OPCODE(lax) { // Undocumented.
  cpu->x = cpu->a = cpu->fetchByteWithMode(mode);
  cpu->evaluateFlags(cpu->a);
}

OPCODE(lda) {
  cpu->a = cpu->fetchByteWithMode(mode);
  cpu->evaluateFlags(cpu->a);
}

OPCODE(ldx) {
  cpu->x = cpu->fetchByteWithMode(mode);
  cpu->evaluateFlags(cpu->x);
}

OPCODE(ldy) {
  cpu->y = cpu->fetchByteWithMode(mode);
  cpu->evaluateFlags(cpu->y);
}
OPCODE(sax) { // Undocumented.
  cpu->bus->write(cpu->fetchEffectiveModeValue(mode), cpu->a & cpu->x);
}
OPCODE(sta) { cpu->bus->write(cpu->fetchEffectiveModeValue(mode), cpu->a); }
OPCODE(stx) { cpu->bus->write(cpu->fetchEffectiveModeValue(mode), cpu->x); }
OPCODE(sty) { cpu->bus->write(cpu->fetchEffectiveModeValue(mode), cpu->y); }
