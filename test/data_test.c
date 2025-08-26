#include "test_suite.h"

void test_integer() {
    Object* five = object_integer(5);

    Int value = INT(five);
    assert(value == 5);

    assert(is_integer(five));
    assert(!is_float(five));
    assert(is_number(five));

    assert(!is_zero(five));
    assert(is_zero(object_integer(0)));

    assert_is_not_text(five);
    assert_is_not_null(five);
    assert_is_not_bool(five);
    assert_is_not_coll(five);
}

void test_float() {
    Object* pi = object_float(3.141);

    Float value = FLOAT(pi);
    assert(value == 3.141);

    assert(is_float(pi));
    assert(!is_integer(pi));
    assert(is_number(pi));

    assert(!is_zero(pi));
    assert(is_zero(object_float(0.0)));

    assert_is_not_text(pi);
    assert_is_not_null(pi);
    assert_is_not_bool(pi);
    assert_is_not_coll(pi);
}

void test_char() {
    Object* x = object_char('x');

    Char value = CHAR(x);
    assert(value == 'x');

    assert(is_char(x));
    assert(!is_string(x));
    assert(!is_symbol(x));

    assert_is_not_number(x);
    assert_is_not_null(x);
    assert_is_not_bool(x);
    assert_is_not_coll(x);
}

void test_string() {
    Object* greeting = object_string("Hi!");

    Str value = STR(greeting);
    assert(strcmp("Hi!", value) == 0);

    assert(!is_char(greeting));
    assert(is_string(greeting));
    assert(!is_symbol(greeting));

    assert_is_not_number(greeting);
    assert_is_not_null(greeting);
    assert_is_not_bool(greeting);
    assert_is_not_coll(greeting);
}

void test_symbol() {
    Object* def = object_symbol("def");

    Str value = STR(def);
    assert(strcmp("def", value) == 0);

    assert(!is_char(def));
    assert(!is_string(def));
    assert(is_symbol(def));

    assert_is_not_null(def);
    assert_is_not_bool(def);
    assert_is_not_number(def);
    assert_is_not_coll(def);
}

void test_true() {
    Object* t = object_true();

    assert(!is_false(t));
    assert(is_true(t));
    assert(is_bool(t));

    assert_is_not_null(t);
    assert_is_not_text(t);
    assert_is_not_number(t);
    assert_is_not_coll(t);
}

void test_false() {
    Object* f = object_false();

    assert(is_false(f));
    assert(!is_true(f));
    assert(is_bool(f));

    assert_is_not_null(f);
    assert_is_not_text(f);
    assert_is_not_number(f);
    assert_is_not_coll(f);
}

int main() {
    test_integer();
    test_float();
    test_char();
    test_string();
    test_symbol();
    test_true();
    test_false();

    return EXIT_SUCCESS;
}
