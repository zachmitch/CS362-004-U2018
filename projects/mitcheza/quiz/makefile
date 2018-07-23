CFLAGS = -Wall -fpic -coverage -lm -std=c99 

all: tests

tests: testme.c
	gcc -o testme testme.c $(CFLAGS)
	-testme
	gcov testme.c
