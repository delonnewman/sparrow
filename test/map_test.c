#include "sparrow.h"
#include <assert.h>

void test_make_map() {
    Object* map = make_map();

    assert(is_map(map));
    assert(is_empty(map));
    assert(length(map) == 0);
}

void test_map_set_and_get() {
    Object* map = make_map();
    map_set(map, object_string("a"), object_integer(1));
    map_set(map, object_string("b"), object_integer(2));
    map_set(map, object_string("c"), object_integer(3));
    map_set(map, object_string("d"), object_integer(4));
    map_set(map, object_string("e"), object_integer(5));
    map_set(map, object_string("f"), object_integer(6));

    Object* value = map_get(map, object_string("a"));
    assert(!is_null(value));
    assert(is_equal(value, object_integer(1)));

    value = map_get(map, object_string("f"));
    assert(!is_null(value));
    assert(is_equal(value, object_integer(6)));

    value = map_get(map, object_string("d"));
    assert(!is_null(value));
    assert(is_equal(value, object_integer(4)));
}

int main() {
  test_make_map();
  test_map_set_and_get();

  return EXIT_SUCCESS;
}
