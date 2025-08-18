#include "sparrow.h"
#include <assert.h>

void test_empty() {
  Object* list = list_empty();

  assert(is_empty(list));
}

void test_empty_count() {
  Object* list = list_empty();

  assert(count(list) == 0);
}

void test_cons() {
  Object* list = list_empty();
  list = list_cons(object_integer(1), list);

  assert(is_equal(list_first(list), object_integer(1)));
  assert(count(list) == 1);
}

void test_first() {
  Object* empty = list_empty();

  assert(is_null(list_first(empty)));
}

void test_next() {
  Object* empty = list_empty();

  assert(is_null(list_next(empty)));
}

int main() {
  test_empty();
  test_empty_count();
  test_cons();
  test_first();
  test_next();

  return EXIT_SUCCESS;
}
