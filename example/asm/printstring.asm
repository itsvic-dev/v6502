MSGPTR = $00

JMP MAIN

MESSAGE: .byte "hello, world!", $a, 0
MESSAGE2: .byte "this is a basic PRTSTR routine", $a, 0

PRTSTR:
    ldy #0
PRTSTR_LOOP:
    lda (MSGPTR),Y
    beq PRTSTR_END
    sta $0200
    iny
    jmp PRTSTR_LOOP
PRTSTR_END:
    rts

MAIN:
    ; move the pointer to MESSAGE to MSGPTR
    lda #<MESSAGE
    sta MSGPTR
    lda #>MESSAGE
    sta MSGPTR+1
    jsr PRTSTR

    lda #<MESSAGE2
    sta MSGPTR
    lda #>MESSAGE2
    sta MSGPTR+1
    jsr PRTSTR
