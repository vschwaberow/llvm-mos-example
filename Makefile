SHELL:=/bin/bash
all: prg d64
prg:
	mos-c64-clang++ -Os -o intro.prg main.cpp
d64:
	c1541 -format "intro",id d64 intro.d64 -attach intro.d64 -write intro.prg intro
clean:
	rm -f *.prg *.elf *.d64
