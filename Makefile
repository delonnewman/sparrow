.POSIX:

CC      = cc
CFLAGS  = -std=c99 -Wall -Wextra -Wno-missing-field-initializers
LDFLAGS =
LDLIBS  =

all: lisp

clean:
	rm lisp lisp.o

lisp.o:
	$(CC) -c $(CFLAGS) -o lisp.o lisp.c

lisp$(EXE): lisp.o
	$(CC) $(CFLAGS) -o $@ main.c lisp.o $(LDLIBS)

run: lisp
	./lisp


.PHONY: all clean run
