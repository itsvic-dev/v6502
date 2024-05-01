all: jumps.bin wozmon.bin printstring.bin
.PHONY: all

%.bin: %.asm loadram.cfg
	ca65 $< -o $(patsubst %.asm,%.o,$<)
	ld65 -C loadram.cfg $(patsubst %.asm,%.o,$<) -o $@

clean:
	rm *.bin *.o
.PHONY: clean
