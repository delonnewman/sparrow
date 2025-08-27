#include "test_suite.h"

void test_make_array() {
  Object* array = make_array(10);

  assert(is_array(array));
  assert(length(array) == 10);
}

void test_array_at_and_set() {
  Object* array = make_array(2);

  array_set(array, 0, object_integer(1));
  assert(is_equal(array_at(array, 0), object_integer(1)));

  array_set(array, 1, object_integer(2));
  assert(is_equal(array_at(array, 1), object_integer(2)));

  // out of range
  assert(is_equal(array_at(array, 2), object_null()));

  // reverse lookup
  assert(is_equal(array_at(array, -1), object_integer(2)));
}

void test_array_at_empty() {
  Object* array = make_array(0);

  assert(is_empty(array));
  assert(is_null(array_at(array, 0)));
}

void test_is_array_null_safe() {
  assert(!is_array(NULL));
}

int main() {
  test_make_array();
  test_array_at_and_set();
  test_array_at_empty();
  test_is_array_null_safe();

  return EXIT_SUCCESS;
}
