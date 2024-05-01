#include "v6502/opcodes.h"

OPCODE(tax) {
  (void)mode;
  cpu->x = cpu->a;
  cpu->evaluateFlags(cpu->x);
}

OPCODE(tay) {
  (void)mode;
  cpu->y = cpu->a;
  cpu->evaluateFlags(cpu->y);
}

OPCODE(tsx) {
  (void)mode;
  cpu->x = cpu->sp;
  cpu->evaluateFlags(cpu->x);
}

OPCODE(txa) {
  (void)mode;
  cpu->a = cpu->x;
  cpu->evaluateFlags(cpu->a);
}

OPCODE(txs) {
  (void)mode;
  cpu->sp = cpu->x;
}

OPCODE(tya) {
  (void)mode;
  cpu->a = cpu->y;
  cpu->evaluateFlags(cpu->a);
}
