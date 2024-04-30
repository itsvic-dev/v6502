all: jumps.bin wozmon.bin
.PHONY: all

jumps.bin: jumps.asm
wozmon.bin: wozmon.asm

%.bin: %.asm
	ca65 $< -o $(patsubst %.asm,%.o,$<)
	ld65 -C loadram.cfg $(patsubst %.asm,%.o,$<) -o $@

clean:
	rm *.bin *.o
.PHONY: clean
