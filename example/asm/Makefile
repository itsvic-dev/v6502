all: wozmon.bin klaus-functional.bin
.PHONY: all

klaus-functional.bin: klaus-functional.asm klaus.cfg
	ca65 $< -o $(patsubst %.asm,%.o,$<)
	ld65 -C klaus.cfg $(patsubst %.asm,%.o,$<) -o $@

%.bin: %.asm loadram.cfg
	ca65 $< -o $(patsubst %.asm,%.o,$<)
	ld65 -C loadram.cfg $(patsubst %.asm,%.o,$<) -o $@

clean:
	rm *.bin *.o
.PHONY: clean
