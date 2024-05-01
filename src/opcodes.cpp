#include "v6502/opcodes.h"
#include "v6502/modes.h"

// load
OPCODE(lda);
OPCODE(sta);
OPCODE(ldx);
OPCODE(stx);
OPCODE(ldy);
OPCODE(sty);

// stack
OPCODE(pha);
OPCODE(php);
OPCODE(pla);
OPCODE(plp);

// logic
OPCODE(_and);
OPCODE(bit);
OPCODE(eor);
OPCODE(ora);

// ctrl
OPCODE(jmp);
OPCODE(jsr);
OPCODE(rti);
OPCODE(rts);

// flags
OPCODE(clc);
OPCODE(cld);
OPCODE(cli);
OPCODE(clv);
OPCODE(sec);
OPCODE(sed);
OPCODE(sei);

// nop
OPCODE(nop) {
  (void)cpu;
  (void)mode;
}

std::map<uint8_t, Opcode> cpuOpcodes = {
    // load
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

    // stack
    {0x48, {"PHA", pha}},
    {0x68, {"PLA", pla}},
    {0x08, {"PHP", php}},
    {0x28, {"PLP", plp}},

    // logic
    {0x29, {"AND #$nn", _and, IMMEDIATE}},
    {0x2D, {"AND $nnnn", _and, ABSOLUTE}},
    {0x3D, {"AND $nnnn,X", _and, X_ABSOLUTE}},
    {0x39, {"AND $nnnn,Y", _and, Y_ABSOLUTE}},
    {0x25, {"AND $nn", _and, ZERO_PAGE}},
    {0x35, {"AND $nn,X", _and, X_ZERO_PAGE}},
    {0x21, {"AND ($nn,X)", _and, X_ZP_INDIRECT}},
    {0x31, {"AND ($nn),Y", _and, ZP_INDIRECT_Y}},

    {0x2C, {"BIT $nnnn", bit, ABSOLUTE}},
    {0x24, {"BIT $nn", bit, ZERO_PAGE}},

    {0x49, {"EOR #$nn", eor, IMMEDIATE}},
    {0x4D, {"EOR $nnnn", eor, ABSOLUTE}},
    {0x5D, {"EOR $nnnn,X", eor, X_ABSOLUTE}},
    {0x59, {"EOR $nnnn,Y", eor, Y_ABSOLUTE}},
    {0x45, {"EOR $nn", eor, ZERO_PAGE}},
    {0x55, {"EOR $nn,X", eor, X_ZERO_PAGE}},
    {0x41, {"EOR ($nn,X)", eor, X_ZP_INDIRECT}},
    {0x51, {"EOR ($nn),Y", eor, ZP_INDIRECT_Y}},

    {0x09, {"ORA #$nn", ora, IMMEDIATE}},
    {0x0D, {"ORA $nnnn", ora, ABSOLUTE}},
    {0x1D, {"ORA $nnnn,X", ora, X_ABSOLUTE}},
    {0x19, {"ORA $nnnn,Y", ora, Y_ABSOLUTE}},
    {0x05, {"ORA $nn", ora, ZERO_PAGE}},
    {0x15, {"ORA $nn,X", ora, X_ZERO_PAGE}},
    {0x01, {"ORA ($nn,X)", ora, X_ZP_INDIRECT}},
    {0x11, {"ORA ($nn),Y", ora, ZP_INDIRECT_Y}},

    // ctrl
    {0x4C, {"JMP $nnnn", jmp, ABSOLUTE}},
    {0x6C, {"JMP ($nnnn)", jmp, ABSOLUTE_INDIRECT}},
    {0x20, {"JSR $nnnn", jsr, ABSOLUTE}},
    {0x40, {"RTI", rti}},
    {0x60, {"RTS", rts}},

    // flags
    {0x18, {"CLC", clc}},
    {0xD8, {"CLD", cld}},
    {0x58, {"CLI", cli}},
    {0xB8, {"CLV", clv}},
    {0x38, {"SEC", sec}},
    {0xF8, {"SED", sed}},
    {0x78, {"SEI", sei}},

    // nop
    {0xEA, {"NOP", nop}},
};
