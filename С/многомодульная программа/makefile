rules.o: rules.h rules.asm
	nasm -f elf32 rules.asm 
res: start_text.c rules.o
	gcc start_text.c rules.o -o pr -m32
run: res
	./pr
