#include "sparrow.h"
#include <assert.h>

void test_object_true() {
    assert(is_true(object_true()));
    assert(!is_true(object_false()));
}

void test_object_false() {
    assert(is_false(object_false()));
    assert(!is_false(object_true()));
}

void test_is_bool() {
  assert(is_bool(object_false()));
  assert(is_bool(object_true()));
}

void test_int_to_bool() {
  assert(is_equal(int_to_bool(0), object_false()));
  assert(is_equal(int_to_bool(1), object_true()));
}

void test_bool_to_int() {
  assert(bool_to_int(object_false()) == 0);
  assert(bool_to_int(object_true()) == 1);
}

int main() {
  test_object_true();
  test_object_false();
  test_is_bool();
  test_int_to_bool();
  test_bool_to_int();

  return EXIT_SUCCESS;
}
