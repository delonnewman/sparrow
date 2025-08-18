#include "sparrow.h"
#include <assert.h>

void test_integer_equality() {
  assert(is_equal(object_integer(1), object_integer(1)));
  assert(!is_equal(object_integer(2), object_integer(1)));
}

void test_float_equality() {
  assert(is_equal(object_float(1.1), object_float(1.1)));
  assert(!is_equal(object_float(1.0), object_float(1.1)));
}

void test_zero_equality() {
  assert(is_equal(object_float(0.0), object_integer(0)));
}

void test_char_equality() {
  assert(is_equal(object_char('a'), object_char('a')));
  assert(!is_equal(object_char('b'), object_char('a')));
}

void test_string_equality() {
  assert(is_equal(object_string("Hey!"), object_string("Hey!")));
  assert(!is_equal(object_string("Ho!"), object_string("Hey!")));
}

void test_symbol_equality() {
  assert(is_equal(object_symbol("def"), object_symbol("def")));
  assert(!is_equal(object_symbol("let"), object_symbol("def")));
}

void test_list_equality() {
  Object* list1 = list_cons(object_integer(1), list_cons(object_integer(2), list_empty()));
  Object* list2 = list_cons(object_integer(1), list_cons(object_integer(2), list_empty()));
  Object* list3 = list_cons(object_integer(2), list_cons(object_integer(1), list_empty()));

  assert(is_equal(list1, list2));
  assert(!is_equal(list1, list3));
}

void test_numerical_equality() {
  assert(is_equal(object_float(1.0), object_integer(1)));
  assert(is_equal(object_integer(3), object_float(3.00)));
  assert(!is_equal(object_integer(3), object_float(3.14)));
}

int main() {
  test_integer_equality();
  test_float_equality();
  test_char_equality();
  test_string_equality();
  test_symbol_equality();
  test_list_equality();
  test_numerical_equality();
  test_zero_equality();

  return EXIT_SUCCESS;
}
