#include "sparrow.h"
#include <assert.h>

void test_make_array() {
  assert(is_array(make_array(0)));
}

void test_array_at_and_set() {
  Object* array = make_array(2);

  array_set(array, 0, object_integer(1));
  assert(is_equal(array_at(array, 0), object_integer(1)));
}

void test_array_at_empty() {
  Object* array = make_array(0);

  assert(is_null(array_at(array, 0)));
}

int main() {
  test_make_array();
  test_array_at_and_set();
  test_array_at_empty();

  return EXIT_SUCCESS;
}
