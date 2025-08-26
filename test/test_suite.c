#include "test_suite.h"

void assert_is_not_coll(Object* obj) {
    assert(!is_cons(obj));
    assert(!is_list(obj));
    assert(!is_coll(obj));
    assert(!is_countable(obj));
}

void assert_is_not_number(Object* obj) {
    assert(!is_float(obj));
    assert(!is_integer(obj));
    assert(!is_number(obj));
    assert(!is_zero(obj));
}

void assert_is_not_text(Object* obj) {
    assert(!is_char(obj));
    assert(!is_string(obj));
    assert(!is_symbol(obj));
}

void assert_is_not_null(Object* obj) {
    assert(is_object(obj));
    assert(!is_null(obj));
}

void assert_is_not_bool(Object* obj) {
    assert(!is_false(obj));
    assert(!is_true(obj));
    assert(!is_bool(obj));
}
