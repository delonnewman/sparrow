.PHONY: all clean run

all: lisp

clean:
	rm lisp

lisp:
	cc -Wall -o lisp main.c

run:
	./lisp