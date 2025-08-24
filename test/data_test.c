#include "sparrow.h"
#include <assert.h>

void test_integer() {
    Object* five = object_integer(5);
    Int value = INT(five);
    assert(value == 5);
}

void test_float() {
    Object* pi = object_float(3.141);
    Float value = FLOAT(pi);
    assert(value == 3.141);
}

void test_char() {
    Object* x = object_char('x');
    Char value = CHAR(x);
    assert(value == 'x');
}

void test_string() {
    Object* greeting = object_string("Hi!");
    Str value = STR(greeting);
    assert(strcmp("Hi!", value) == 0);
}

int main() {
    test_integer();
    test_float();
    test_char();
    test_string();

    return EXIT_SUCCESS;
}
