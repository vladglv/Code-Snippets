# Makefile
CC=clang -g -O0 -fPIC -D_XOPEN_SOURCE=700 -std=c11 -Wmain -W -Wall -Wthread-safety -pedantic -pedantic-errors -fsanitize=address,undefined,leak
EXECUTABLE1=fptohex
EXECUTABLE2=hextofp

SOURCES=fphex.c

all:
	$(CC) -o $(EXECUTABLE1) $(SOURCES)
	cp $(EXECUTABLE1) $(EXECUTABLE2)

clean:
	rm $(EXECUTABLE1) $(EXECUTABLE2)
