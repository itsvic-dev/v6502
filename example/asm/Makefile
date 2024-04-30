all: jumps.bin
.PHONY: all

jumps.bin: jumps.asm

%.bin: %.asm
	ca65 $< -o $(patsubst %.asm,%.o,$<)
	ld65 -C loadram.cfg $(patsubst %.asm,%.o,$<) -o $@

clean:
	rm *.bin *.o
.PHONY: clean
