#include "cpu/cpu.h"
#include "cpu/opcodes.h"

OPCODE(clc) {
  (void)mode;
  cpu->clearFlags(STATUS_CARRY);
}

OPCODE(cld) {
  (void)mode;
  cpu->clearFlags(STATUS_DECIMAL);
}

OPCODE(cli) {
  (void)mode;
  cpu->clearFlags(STATUS_INTERRUPT_DISABLE);
}

OPCODE(clv) {
  (void)mode;
  cpu->clearFlags(STATUS_OVERFLOW);
}

OPCODE(sec) {
  (void)mode;
  cpu->setFlags(STATUS_CARRY);
}

OPCODE(sed) {
  (void)mode;
  cpu->setFlags(STATUS_DECIMAL);
}

OPCODE(sei) {
  (void)mode;
  cpu->setFlags(STATUS_INTERRUPT_DISABLE);
}
