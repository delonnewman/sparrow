.POSIX:

CC       = cc
CFLAGS   = -std=c99 -Wall -Wextra -Wno-missing-field-initializers
LDFLAGS  =
LDLIBS   =
SRC      = src
NAME     = sparrow
TEST_DIR = test

all: $(NAME)

clean:
	rm -f $(NAME) $(NAME).o
	rm -f lisp$(EXE)
	rm -f $$(ls test/*_test)

$(NAME).o:
	$(CC) -c $(CFLAGS) -o $@ $(SRC)/$(NAME).c

lisp$(EXE): $(NAME).o
	$(CC) $(CFLAGS) -o $@ $(SRC)/main.c $(NAME).o $(LDLIBS)

run: lisp$(EXE)
	./lisp$(EXE)

test: $(TEST_DIR)/*_test.c
	@for file in $^; do \
		test=`echo $$file | sed 's/^test\///' | sed 's/_test.c//'`; \
		make run_test TEST=$$test; \
	done

run_test: compile_test
	./test/$(TEST)_test$(EXE)

compile_test: $(NAME).o
	$(CC) $(CFLAGS) -I$(SRC) -o ./test/$(TEST)_test$(EXE) test/test_suite.c test/$(TEST)_test.c $(NAME).o $(LDLIBS)

clean_test: $(TEST_DIR)/*_test
ifdef TEST
	rm -rf $(TEST)
else
	rm -rf $^
endif

.PHONY: all clean run test run_test compile_test clean_test
