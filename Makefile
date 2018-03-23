CC = cc
CFLAGS = -O2 -Wall -c -o $@


all: ajtak

ajtak: src/main.o 
	$(CC) -Wall -o $@ src/main.o

src/main.o: src/main.c

clean:
	rm -f src/*.o *.exe src/*.res ajtak

