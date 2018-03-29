CC = cc
CFLAGS = -O2 -Wall -c -o $@


all: ajtak

ajtak: src/main.o 
	$(CC) -Wall -o $@ src/main.o

src/main.o: src/main.c src/main.h src/map.h

clean:
	rm -f src/*.o *.exe src/*.res ajtak

