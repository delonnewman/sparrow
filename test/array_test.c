#include "lisp.h"
#include <assert.h>

void test_array_new() {
  assert(is_array(array_new(0)));
}

int main() {
  test_array_new();

  return EXIT_SUCCESS;
}
