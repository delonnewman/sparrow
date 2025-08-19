#include "sparrow.h"
#include <assert.h>

void test_string_hash() {
    long x = object_hash_code(object_string("Hey You"));
    long y = object_hash_code(object_string("Hey You"));
    long z = object_hash_code(object_string("Hey You!"));

    assert(x == y);
    assert(x != z);
}

int main() {
  test_string_hash();

  return EXIT_SUCCESS;
}
