#include "sparrow.h"
#include <assert.h>

void test_make_map() {
    assert(is_map(make_map()));
}

int main() {
  test_make_map();

  return EXIT_SUCCESS;
}
