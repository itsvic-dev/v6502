#include "cpu/cpu.h"
#include "cpu/opcodes.h"

// defines LDA, LDX, LDY

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
