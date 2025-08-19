#include "sparrow.h"
#include <assert.h>

void test_null_safe_predicates() {
    assert(!is_integer(NULL));
    assert(!is_float(NULL));
    assert(!is_number(NULL));
    assert(!is_zero(NULL));
}

void test_is_object() {
    assert(is_object(object_null()));
    assert(is_object(object_false()));
    assert(is_object(object_true()));
    assert(is_object(object_integer(0)));
    assert(is_object(object_float(0.0)));
    assert(is_object(object_char('a')));
    assert(is_object(object_string("Hey!")));
    assert(is_object(object_symbol("def")));
    assert(!is_object(NULL));
}

int main() {
    test_null_safe_predicates();
    test_is_object();

    return EXIT_SUCCESS;
}
