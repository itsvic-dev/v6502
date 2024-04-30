#include "cpu/opcodes.h"
#include "cpu/modes.h"

OPCODE(lda);
OPCODE(sta);
OPCODE(ldx);
OPCODE(stx);
OPCODE(ldy);
OPCODE(sty);

std::map<uint8_t, Opcode> cpuOpcodes = {
    {0xA9, {"LDA #$nn", lda, IMMEDIATE}},
    {0xAD, {"LDA $nnnn", lda, ABSOLUTE}},
    {0xBD, {"LDA $nnnn,X", lda, X_ABSOLUTE}},
    {0xB9, {"LDA $nnnn,Y", lda, Y_ABSOLUTE}},
    {0xA5, {"LDA $nn", lda, ZERO_PAGE}},
    {0xB5, {"LDA $nn,X", lda, X_ZERO_PAGE}},
    {0xA1, {"LDA ($nn,X)", lda, X_ZP_INDIRECT}},
    {0xB1, {"LDA ($nn),Y", lda, ZP_INDIRECT_Y}},

    {0x8D, {"STA $nnnn", sta, ABSOLUTE}},
    {0x9D, {"STA $nnnn,X", sta, X_ABSOLUTE}},
    {0x99, {"STA $nnnn,Y", sta, Y_ABSOLUTE}},
    {0x85, {"STA $nn", sta, ZERO_PAGE}},
    {0x95, {"STA $nn,X", sta, X_ZERO_PAGE}},
    {0x81, {"STA ($nn,X)", sta, X_ZP_INDIRECT}},
    {0x91, {"STA ($nn),Y", sta, ZP_INDIRECT_Y}},

    {0xA2, {"LDX #$nn", ldx, IMMEDIATE}},
    {0xAE, {"LDX $nnnn", ldx, ABSOLUTE}},
    {0xBE, {"LDX $nnnn,Y", ldx, Y_ABSOLUTE}},
    {0xA6, {"LDX $nn", ldx, ZERO_PAGE}},
    {0xB6, {"LDX $nn,Y", ldx, Y_ZERO_PAGE}},

    {0x8E, {"STX $nnnn", stx, ABSOLUTE}},
    {0x86, {"STX $nn", stx, ZERO_PAGE}},
    {0x96, {"STX $nn,Y", stx, Y_ZERO_PAGE}},

    {0xA0, {"LDY #$nn", ldy, IMMEDIATE}},
    {0xAC, {"LDY $nnnn", ldy, ABSOLUTE}},
    {0xBC, {"LDY $nnnn,X", ldy, X_ABSOLUTE}},
    {0xA4, {"LDY $nn", ldy, ZERO_PAGE}},
    {0xB4, {"LDY $nn,X", ldy, X_ZERO_PAGE}},

    {0x8C, {"STY $nnnn", sty, ABSOLUTE}},
    {0x84, {"STY $nn", sty, ZERO_PAGE}},
    {0x94, {"STY $nn,X", sty, X_ZERO_PAGE}},
};
