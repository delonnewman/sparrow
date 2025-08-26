#include "sparrow.h"
#include <assert.h>

void test_empty() {
  Object* list = list_empty();

  assert(is_list(list));
  assert(is_empty(list));
  assert(length(list) == 0);

  assert(is_null(list_first(list)));
  assert(is_null(list_next(list)));
}

void test_cons() {
  Object* list = list_cons(object_integer(3), list_cons(object_integer(2), list_empty()));

  assert(is_list(list));
  assert(length(list) == 2);

  Object* obj = list_first(list);
  assert(obj->type == TYPE_INT);
  Int value = INT(obj);
  assert(value == 3);

  obj = list_first(list_next(list));
  value = INT(obj);
  assert(value == 2);

  obj = list_next(list_next(list));
  assert(is_empty(obj));

  obj = list_first(list_next(list_next(list)));
  assert(is_null(obj));

  obj = list_next(list_next(list_next(list)));
  assert(is_null(obj));
}

void test_cons_and_null() {
  Object* obj = object_null();
  Object* list = list_cons(object_integer(1), obj);

  assert(is_null(obj));
  assert(length(list) == 1);

  assert(!is_null(list_next(list)));
  assert(is_equal(list_first(list), object_integer(1)));
}

void test_is_list() {
  Object* list = list_empty();

  assert(is_list(list));
  assert(is_cons(list));
}

void test_pair() {
  Object* pair = make_pair(object_integer(1), object_integer(2));

  assert(is_pair(pair));
  assert(is_cons(pair));
  assert(is_equal(pair_key(pair), object_integer(1)));
  assert(is_equal(pair_value(pair), object_integer(2)));
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
  test_pair();

  return EXIT_SUCCESS;
}
