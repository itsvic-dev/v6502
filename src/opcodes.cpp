#include "v6502/opcodes.h"
#include "v6502/opcodeMap.h"

// load
OPCODE(lda);
OPCODE(sta);
OPCODE(ldx);
OPCODE(stx);
OPCODE(ldy);
OPCODE(sty);

// trans
OPCODE(tax);
OPCODE(tay);
OPCODE(tsx);
OPCODE(txa);
OPCODE(txs);
OPCODE(tya);

// stack
OPCODE(pha);
OPCODE(php);
OPCODE(pla);
OPCODE(plp);

// shift
OPCODE(asl);
OPCODE(lsr);
OPCODE(rol);
OPCODE(ror);

// logic
OPCODE(_and);
OPCODE(bit);
OPCODE(eor);
OPCODE(ora);

// arith
OPCODE(adc);
OPCODE(cmp);
OPCODE(cpx);
OPCODE(cpy);
OPCODE(sbc);

// inc
OPCODE(dec);
OPCODE(dex);
OPCODE(dey);
OPCODE(inc);
OPCODE(inx);
OPCODE(iny);

// ctrl
OPCODE(brk);
OPCODE(jmp);
OPCODE(jsr);
OPCODE(rti);
OPCODE(rts);

// branch
OPCODE(bcc);
OPCODE(bcs);
OPCODE(beq);
OPCODE(bmi);
OPCODE(bne);
OPCODE(bpl);
OPCODE(bvc);
OPCODE(bvs);

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
    {0xA9, {"LDA #$%02x", lda, IMMEDIATE}},
    {0xAD, {"LDA $%04x", lda, ABSOLUTE}},
    {0xBD, {"LDA $%04x,X", lda, X_ABSOLUTE}},
    {0xB9, {"LDA $%04x,Y", lda, Y_ABSOLUTE}},
    {0xA5, {"LDA $%02x", lda, ZERO_PAGE}},
    {0xB5, {"LDA $%02x,X", lda, X_ZERO_PAGE}},
    {0xA1, {"LDA ($%02x,X)", lda, X_ZP_INDIRECT}},
    {0xB1, {"LDA ($%02x),Y", lda, ZP_INDIRECT_Y}},

    {0x8D, {"STA $%04x", sta, ABSOLUTE}},
    {0x9D, {"STA $%04x,X", sta, X_ABSOLUTE}},
    {0x99, {"STA $%04x,Y", sta, Y_ABSOLUTE}},
    {0x85, {"STA $%02x", sta, ZERO_PAGE}},
    {0x95, {"STA $%02x,X", sta, X_ZERO_PAGE}},
    {0x81, {"STA ($%02x,X)", sta, X_ZP_INDIRECT}},
    {0x91, {"STA ($%02x),Y", sta, ZP_INDIRECT_Y}},

    {0xA2, {"LDX #$%02x", ldx, IMMEDIATE}},
    {0xAE, {"LDX $%04x", ldx, ABSOLUTE}},
    {0xBE, {"LDX $%04x,Y", ldx, Y_ABSOLUTE}},
    {0xA6, {"LDX $%02x", ldx, ZERO_PAGE}},
    {0xB6, {"LDX $%02x,Y", ldx, Y_ZERO_PAGE}},

    {0x8E, {"STX $%04x", stx, ABSOLUTE}},
    {0x86, {"STX $%02x", stx, ZERO_PAGE}},
    {0x96, {"STX $%02x,Y", stx, Y_ZERO_PAGE}},

    {0xA0, {"LDY #$%02x", ldy, IMMEDIATE}},
    {0xAC, {"LDY $%04x", ldy, ABSOLUTE}},
    {0xBC, {"LDY $%04x,X", ldy, X_ABSOLUTE}},
    {0xA4, {"LDY $%02x", ldy, ZERO_PAGE}},
    {0xB4, {"LDY $%02x,X", ldy, X_ZERO_PAGE}},

    {0x8C, {"STY $%04x", sty, ABSOLUTE}},
    {0x84, {"STY $%02x", sty, ZERO_PAGE}},
    {0x94, {"STY $%02x,X", sty, X_ZERO_PAGE}},

    // trans
    {0xAA, {"TAX", tax}},
    {0xA8, {"TAY", tay}},
    {0xBA, {"TSX", tsx}},
    {0x8A, {"TXA", txa}},
    {0x9A, {"TXS", txs}},
    {0x98, {"TYA", tya}},

    // stack
    {0x48, {"PHA", pha}},
    {0x68, {"PLA", pla}},
    {0x08, {"PHP", php}},
    {0x28, {"PLP", plp}},

    // shift
    {0x0A, {"ASL A", asl, ACCUMULATOR}},
    {0x0E, {"ASL $%04x", asl, ABSOLUTE}},
    {0x1E, {"ASL $%04x,X", asl, X_ABSOLUTE}},
    {0x06, {"ASL $%02x", asl, ZERO_PAGE}},
    {0x16, {"ASL $%02x,X", asl, X_ZERO_PAGE}},

    {0x4A, {"LSR A", lsr, ACCUMULATOR}},
    {0x4E, {"LSR $%04x", lsr, ABSOLUTE}},
    {0x5E, {"LSR $%04x,X", lsr, X_ABSOLUTE}},
    {0x46, {"LSR $%02x", lsr, ZERO_PAGE}},
    {0x56, {"LSR $%02x,X", lsr, X_ZERO_PAGE}},

    {0x2A, {"ROL A", rol, ACCUMULATOR}},
    {0x2E, {"ROL $%04x", rol, ABSOLUTE}},
    {0x3E, {"ROL $%04x,X", rol, X_ABSOLUTE}},
    {0x26, {"ROL $%02x", rol, ZERO_PAGE}},
    {0x36, {"ROL $%02x,X", rol, X_ZERO_PAGE}},

    {0x6A, {"ROR A", ror, ACCUMULATOR}},
    {0x6E, {"ROR $%04x", ror, ABSOLUTE}},
    {0x7E, {"ROR $%04x,X", ror, X_ABSOLUTE}},
    {0x66, {"ROR $%02x", ror, ZERO_PAGE}},
    {0x76, {"ROR $%02x,X", ror, X_ZERO_PAGE}},

    // logic
    {0x29, {"AND #$%02x", _and, IMMEDIATE}},
    {0x2D, {"AND $%04x", _and, ABSOLUTE}},
    {0x3D, {"AND $%04x,X", _and, X_ABSOLUTE}},
    {0x39, {"AND $%04x,Y", _and, Y_ABSOLUTE}},
    {0x25, {"AND $%02x", _and, ZERO_PAGE}},
    {0x35, {"AND $%02x,X", _and, X_ZERO_PAGE}},
    {0x21, {"AND ($%02x,X)", _and, X_ZP_INDIRECT}},
    {0x31, {"AND ($%02x),Y", _and, ZP_INDIRECT_Y}},

    {0x2C, {"BIT $%04x", bit, ABSOLUTE}},
    {0x24, {"BIT $%02x", bit, ZERO_PAGE}},

    {0x49, {"EOR #$%02x", eor, IMMEDIATE}},
    {0x4D, {"EOR $%04x", eor, ABSOLUTE}},
    {0x5D, {"EOR $%04x,X", eor, X_ABSOLUTE}},
    {0x59, {"EOR $%04x,Y", eor, Y_ABSOLUTE}},
    {0x45, {"EOR $%02x", eor, ZERO_PAGE}},
    {0x55, {"EOR $%02x,X", eor, X_ZERO_PAGE}},
    {0x41, {"EOR ($%02x,X)", eor, X_ZP_INDIRECT}},
    {0x51, {"EOR ($%02x),Y", eor, ZP_INDIRECT_Y}},

    {0x09, {"ORA #$%02x", ora, IMMEDIATE}},
    {0x0D, {"ORA $%04x", ora, ABSOLUTE}},
    {0x1D, {"ORA $%04x,X", ora, X_ABSOLUTE}},
    {0x19, {"ORA $%04x,Y", ora, Y_ABSOLUTE}},
    {0x05, {"ORA $%02x", ora, ZERO_PAGE}},
    {0x15, {"ORA $%02x,X", ora, X_ZERO_PAGE}},
    {0x01, {"ORA ($%02x,X)", ora, X_ZP_INDIRECT}},
    {0x11, {"ORA ($%02x),Y", ora, ZP_INDIRECT_Y}},

    // arith
    {0x69, {"ADC #$%02x", adc, IMMEDIATE}},
    {0x6D, {"ADC $%04x", adc, ABSOLUTE}},
    {0x7D, {"ADC $%04x,X", adc, X_ABSOLUTE}},
    {0x79, {"ADC $%04x,Y", adc, Y_ABSOLUTE}},
    {0x65, {"ADC $%02x", adc, ZERO_PAGE}},
    {0x75, {"ADC $%02x,X", adc, X_ZERO_PAGE}},
    {0x61, {"ADC ($%02x,X)", adc, X_ZP_INDIRECT}},
    {0x71, {"ADC ($%02x),Y", adc, ZP_INDIRECT_Y}},

    {0xC9, {"CMP #$%02x", cmp, IMMEDIATE}},
    {0xCD, {"CMP $%04x", cmp, ABSOLUTE}},
    {0xDD, {"CMP $%04x,X", cmp, X_ABSOLUTE}},
    {0xD9, {"CMP $%04x,Y", cmp, Y_ABSOLUTE}},
    {0xC5, {"CMP $%02x", cmp, ZERO_PAGE}},
    {0xD5, {"CMP $%02x,X", cmp, X_ZERO_PAGE}},
    {0xC1, {"CMP ($%02x,X)", cmp, X_ZP_INDIRECT}},
    {0xD1, {"CMP ($%02x),Y", cmp, ZP_INDIRECT_Y}},

    {0xE0, {"CPX #$%02x", cpx, IMMEDIATE}},
    {0xEC, {"CPX $%04x", cpx, ABSOLUTE}},
    {0xE4, {"CPX $%02x", cpx, ZERO_PAGE}},

    {0xC0, {"CPY #$%02x", cpy, IMMEDIATE}},
    {0xCC, {"CPY $%04x", cpy, ABSOLUTE}},
    {0xC4, {"CPY $%02x", cpy, ZERO_PAGE}},

    {0xE9, {"SBC #$%02x", sbc, IMMEDIATE}},
    {0xED, {"SBC $%04x", sbc, ABSOLUTE}},
    {0xFD, {"SBC $%04x,X", sbc, X_ABSOLUTE}},
    {0xF9, {"SBC $%04x,Y", sbc, Y_ABSOLUTE}},
    {0xE5, {"SBC $%02x", sbc, ZERO_PAGE}},
    {0xF5, {"SBC $%02x,X", sbc, X_ZERO_PAGE}},
    {0xE1, {"SBC ($%02x,X)", sbc, X_ZP_INDIRECT}},
    {0xF1, {"SBC ($%02x),Y", sbc, ZP_INDIRECT_Y}},

    // inc
    {0xCE, {"DEC $%04x", dec, ABSOLUTE}},
    {0xDE, {"DEC $%04x,X", dec, X_ABSOLUTE}},
    {0xC6, {"DEC $%02x", dec, ZERO_PAGE}},
    {0xD6, {"DEC $%02x,X", dec, X_ZERO_PAGE}},
    {0xCA, {"DEX", dex}},
    {0x88, {"DEY", dey}},

    {0xEE, {"INC $%04x", inc, ABSOLUTE}},
    {0xFE, {"INC $%04x,X", inc, X_ABSOLUTE}},
    {0xE6, {"INC $%02x", inc, ZERO_PAGE}},
    {0xF6, {"INC $%02x,X", inc, X_ZERO_PAGE}},
    {0xE8, {"INX", inx}},
    {0xC8, {"INY", iny}},

    // ctrl
    {0x00, {"BRK", brk}},
    {0x4C, {"JMP $%04x", jmp, ABSOLUTE}},
    {0x6C, {"JMP ($%04x)", jmp, ABSOLUTE_INDIRECT}},
    {0x20, {"JSR $%04x", jsr, ABSOLUTE}},
    {0x40, {"RTI", rti}},
    {0x60, {"RTS", rts}},

    // branch
    {0x90, {"BCC $%04x", bcc, RELATIVE}},
    {0xB0, {"BCS $%04x", bcs, RELATIVE}},
    {0xF0, {"BEQ $%04x", beq, RELATIVE}},
    {0x30, {"BMI $%04x", bmi, RELATIVE}},
    {0xD0, {"BNE $%04x", bne, RELATIVE}},
    {0x10, {"BPL $%04x", bpl, RELATIVE}},
    {0x50, {"BVC $%04x", bvc, RELATIVE}},
    {0x70, {"BVS $%04x", bvs, RELATIVE}},

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
