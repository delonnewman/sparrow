#include "lisp.h"
#include <assert.h>

void test_empty() {
  Object* list = list_empty();

  assert(list_is_empty(list));
}

int main() {
  test_empty();

  return EXIT_SUCCESS;
}
