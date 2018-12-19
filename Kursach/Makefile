CC=gcc

all: cw

cw: main.o iotext.o text.o structs_and_memory.o
	$(CC) main.o iotext.o text.o structs_and_memory.o -o cw

main.o: main.c text.h iotext.h structs_and_memory.h
	$(CC) -c main.c

text.o: text.c text.h iotext.h structs_and_memory.h
	$(CC) -c text.c

iotext.o: iotext.c iotext.h structs_and_memory.h
	$(CC) -c iotext.c

structs_and_memory.o: structs_and_memory.c structs_and_memory.h
	$(CC) -c structs_and_memory.c

clear:
	rm -rf *.o cw