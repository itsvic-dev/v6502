#include "cpu/cpu.h"
#include "cpu/opcodes.h"

OPCODE(pha) {
  (void)mode;
  cpu->pushStack(cpu->a);
}

OPCODE(php) {
  (void)mode;
  cpu->pushStack(cpu->status);
}

OPCODE(pla) {
  (void)mode;
  cpu->a = cpu->popStack();
  cpu->evaluateFlags(cpu->a);
}

OPCODE(plp) {
  (void)mode;
  uint8_t mask = ~(STATUS_UNUSED | STATUS_BREAK_COMMAND);
  cpu->status = (cpu->popStack() & mask) | (cpu->status & ~mask);
}
