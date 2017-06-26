# Compiler Options
CC=clang -g -O0 -fPIC -D_XOPEN_SOURCE=700 -std=c11 -Wmain -W -Wall -Wthread-safety -pedantic -pedantic-errors
CCS=-fsanitize=address,undefined,leak

# Executable names
EXECUTABLE=print_sierpinski
EXECUTABLE_VG=print_sierpinski_vg
EXECUTABLELIST=$(EXECUTABLE) $(EXECUTABLE_VG) 

# Sources
SOURCES=print_sierpinski.c

# Targets
all:
	$(CC) $(CCS) -o $(EXECUTABLE) $(SOURCES)
	$(CC) -o $(EXECUTABLE_VG) $(SOURCES)

clean:
	rm $(EXECUTABLELIST)
