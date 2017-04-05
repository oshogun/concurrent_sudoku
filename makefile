CC=gcc
CFLAGS=-std=c11
LIBS=-lpthread
OUTFILE=sudoku 

all: compile
compile:
	$(CC) sudoku-base.c -o $(OUTFILE) $(CFLAGS) $(LIBS)
clean:
	rm sudoku 
