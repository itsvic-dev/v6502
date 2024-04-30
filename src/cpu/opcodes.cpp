#include "cpu/opcodes.h"

OPCODE(lda);
OPCODE(ldx);
OPCODE(ldy);

std::map<uint8_t, Opcode> cpuOpcodes = {
    {0xA9, {"LDA #$nn", lda, IMMEDIATE}},
    {0xAD, {"LDA $nnnn", lda, ABSOLUTE}},
    {0xBD, {"LDA $nnnn,X", lda, X_ABSOLUTE}},
    {0xB9, {"LDA $nnnn,Y", lda, Y_ABSOLUTE}},
    {0xA5, {"LDA $nn", lda, ZERO_PAGE}},
    {0xB5, {"LDA $nn,X", lda, X_ZERO_PAGE}},
    {0xA1, {"LDA ($nn,X)", lda, X_ZP_INDIRECT}},
    {0xB1, {"LDA ($nn),Y", lda, ZP_INDIRECT_Y}},

    {0xA2, {"LDX #$nn", ldx, IMMEDIATE}},
    {0xAE, {"LDX $nnnn", ldx, ABSOLUTE}},
    {0xBE, {"LDX $nnnn,Y", ldx, Y_ABSOLUTE}},
    {0xA6, {"LDX $nn", ldx, ZERO_PAGE}},
    {0xB6, {"LDX $nn,Y", ldx, Y_ZERO_PAGE}},

    {0xA0, {"LDY #$nn", ldy, IMMEDIATE}},
    {0xAC, {"LDY $nnnn", ldy, ABSOLUTE}},
    {0xBC, {"LDY $nnnn,X", ldy, X_ABSOLUTE}},
    {0xA4, {"LDY $nn", ldy, ZERO_PAGE}},
    {0xB4, {"LDY $nn,X", ldy, X_ZERO_PAGE}},
};
