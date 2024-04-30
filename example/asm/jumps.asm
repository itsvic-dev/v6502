.segment "CODE"

jmp main

loadfun:
  lda #69
  rts

main:
  jsr loadfun
  nop
