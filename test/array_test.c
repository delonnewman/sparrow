#include "sparrow.h"
#include <assert.h>

void test_make_array() {
  assert(is_array(make_array(0)));
}

int main() {
  test_make_array();

  return EXIT_SUCCESS;
}
