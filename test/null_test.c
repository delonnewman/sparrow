#include "sparrow.h"
#include <assert.h>

void test_object_null() {
    assert(is_null(object_null()));
}

void test_null_count() {
    assert(count(object_null()) == 0);
}

int main() {
  test_object_null();
  test_null_count();

  return EXIT_SUCCESS;
}
