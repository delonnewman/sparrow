#include "sparrow.h"
#include <assert.h>

void test_empty() {
  Object* list = list_empty();

  assert(is_empty(list));
}

void test_empty_count() {
  Object* list = list_empty();

  assert(collection_count(list) == 0);
}

void test_cons() {
  Object* list = list_empty();
  list = list_cons(object_integer(1), list);

  assert(is_equal(list_first(list), object_integer(1)));
  assert(collection_count(list) == 1);
}

void test_cons_and_null() {
  Object* obj = object_null();
  Object* list = list_cons(object_integer(1), obj);

  assert(is_null(obj));
  assert(!is_null(list_next(list)));

  assert(is_equal(list_first(list), object_integer(1)));
  assert(collection_count(list) == 1);
}

void test_first() {
  Object* empty = list_empty();

  assert(is_null(list_first(empty)));
}

void test_next() {
  Object* empty = list_empty();

  assert(is_null(list_next(empty)));
}

void test_is_list_null_safe() {
  assert(!is_list(NULL));
}

int main() {
  test_empty();
  test_empty_count();
  test_cons();
  test_first();
  test_next();
  test_cons_and_null();
  test_is_list_null_safe();

  return EXIT_SUCCESS;
}
