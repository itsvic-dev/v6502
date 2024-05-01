jmp main

PRHEX:
                AND     #$0F           ; Mask LSD for hex print.
                ORA     #$30           ; Add "0".
                CMP     #$3A           ; Digit?
                BCC     ECHO           ; Yes, output it.
                ADC     #$06           ; Add offset for letter.

ECHO:
                STA     $200           ; Output character.
                RTS                    ; Return.

main:
    lda #$a
    jsr PRHEX
    nop

; cmp #$3A with A=$3A
;               nvdizc
; ground truth: 000111
;        v6502: 000110
