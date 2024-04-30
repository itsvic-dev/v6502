#include "cpu/opcodes.h"

OPCODE(sta) { cpu->bus->write(cpu->fetchEffectiveModeValue(mode), cpu->a); }
OPCODE(stx) { cpu->bus->write(cpu->fetchEffectiveModeValue(mode), cpu->x); }
OPCODE(sty) { cpu->bus->write(cpu->fetchEffectiveModeValue(mode), cpu->y); }
