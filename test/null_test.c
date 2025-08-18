#include "sparrow.h"
#include <assert.h>

void test_object_null() {
    assert(is_null(object_null()));
}

int main() {
  test_object_null();

  return EXIT_SUCCESS;
}
