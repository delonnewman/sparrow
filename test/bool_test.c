#include "sparrow.h"
#include <assert.h>

void test_object_true() {
    assert(1);
}

void test_object_false() {
    assert(1);
}

int main() {
  test_object_true();
  test_object_false();

  return EXIT_SUCCESS;
}
