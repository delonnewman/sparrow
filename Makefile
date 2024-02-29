.POSIX:

CC      = cc
CFLAGS  = -std=c99 -Wall -Wextra -Wno-missing-field-initializers
LDFLAGS =
LDLIBS  =
SRC     = src

all: lisp

clean:
	rm -f lisp lisp.o
	rm -f test/list_test$(EXE)

lisp.o:
	$(CC) -c $(CFLAGS) -o lisp.o $(SRC)/lisp.c

lisp$(EXE): lisp.o
	$(CC) $(CFLAGS) -o $@ $(SRC)/main.c lisp.o $(LDLIBS)

run: lisp
	./lisp$(EXE)

test/list_test$(EXE): lisp.o
	$(CC) $(CFLAGS) -I$(SRC) -o $@ test/list_test.c lisp.o $(LDLIBS)

test: test/list_test$(EXE)
	./test/list_test$(EXE)

.PHONY: all clean run test
