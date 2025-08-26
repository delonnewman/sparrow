#include "sparrow.h"
#include <assert.h>

void test_object_null() {
  Object* null = object_null();

  assert(is_object(null));
  assert(is_null(null));
  assert(is_false(null));
  assert(!is_true(null));
  assert(!is_bool(null));
}

void test_null_count() {
  assert(length(object_null()) == 0);
}

void test_null_is_empty() {
  assert(is_empty(object_null()));
}

int main() {
  test_object_null();
  test_null_count();
  test_null_is_empty();

  return EXIT_SUCCESS;
}
