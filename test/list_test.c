#include "sparrow.h"
#include <assert.h>

void test_empty() {
  Object* list = list_empty();

  assert(is_list(list));
  assert(is_empty(list));
  assert(collection_count(list) == 0);
  assert(is_null(list_first(list)));
  assert(is_null(list_next(list)));
}

void test_cons() {
  Object* list = list_cons(object_integer(1), list_cons(object_integer(2), list_empty()));

  assert(collection_count(list) == 2);
  assert(is_equal(list_first(list), object_integer(1)));
  assert(is_equal(list_first(list_next(list)), object_integer(2)));
  assert(is_empty(list_next(list_next(list))));
  assert(is_null(list_first(list_next(list_next(list)))));
}

void test_cons_and_null() {
  Object* obj = object_null();
  Object* list = list_cons(object_integer(1), obj);

  assert(is_null(obj));
  assert(!is_null(list_next(list)));
  assert(is_equal(list_first(list), object_integer(1)));
  assert(collection_count(list) == 1);
}

void test_is_list() {
  Object* list = list_empty();

  assert(is_list(list));
  assert(is_cons(list));
}

void test_make_pair() {
  Object* pair = make_pair(object_integer(1), object_integer(2));

  assert(is_pair(pair));
  assert(is_cons(pair));
}

void test_list_null_safe_predicates() {
  assert(!is_list(NULL));
  assert(!is_cons(NULL));
}

int main() {
  test_empty();
  test_cons();
  test_cons_and_null();
  test_list_null_safe_predicates();
  test_is_list();
  test_make_pair();

  return EXIT_SUCCESS;
}
