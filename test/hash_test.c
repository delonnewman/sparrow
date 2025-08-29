#include "test_suite.h"

void test_string_hash() {
    long x = object_hash_code(object_string("Hey You"));
    long y = object_hash_code(object_string("Hey You"));
    long z = object_hash_code(object_string("Hey You!"));

    assert(x == y);
    assert(x != z);
}

void test_symbol_hash() {
    long x = object_hash_code(object_symbol("def"));
    long y = object_hash_code(object_symbol("def"));
    long z = object_hash_code(object_symbol("defn"));

    assert(x == y);
    assert(x != z);
}

void test_bool_hash() {
    long x = object_hash_code(object_true());
    long y = object_hash_code(object_true());
    long z = object_hash_code(object_false());

    assert(x == y);
    assert(x != z);
}

void test_int_hash() {
    long x = object_hash_code(object_integer(42));
    long y = object_hash_code(object_integer(42));
    long z = object_hash_code(object_integer(43));

    assert(x == y);
    assert(x != z);
}

void test_float_hash() {
    long x = object_hash_code(object_float(3.14));
    long y = object_hash_code(object_float(3.14));
    long z = object_hash_code(object_float(2.71));

    assert(x == y);
    assert(x != z);
}

void test_char_hash() {
    long x = object_hash_code(object_char('a'));
    long y = object_hash_code(object_char('a'));
    long z = object_hash_code(object_char('b'));

    assert(x == y);
    assert(x != z);
}

void test_list_hash() {
    Object* list1 = list_cons(object_integer(1), list_cons(object_integer(2), list_empty()));
    Object* list2 = list_cons(object_integer(1), list_cons(object_integer(2), list_empty()));
    Object* list3 = list_cons(object_integer(2), list_cons(object_integer(3), list_empty()));

    long x = object_hash_code(list1);
    long y = object_hash_code(list2);
    long z = object_hash_code(list3);

    assert(x == y);
    assert(x != z);
}

void test_pair_hash() {
    Object* pair1 = make_pair(object_integer(1), object_integer(2));
    Object* pair2 = make_pair(object_integer(1), object_integer(2));
    Object* pair3 = make_pair(object_integer(2), object_integer(3));

    long x = object_hash_code(pair1);
    long y = object_hash_code(pair2);
    long z = object_hash_code(pair3);

    assert(x == y);
    assert(x != z);
}

void test_array_hash() {
    Object* array1 = make_array(3);
    array_set(array1, 0, object_integer(1));
    array_set(array1, 1, object_integer(2));
    array_set(array1, 2, object_integer(3));

    Object* array2 = make_array(3);
    array_set(array2, 0, object_integer(1));
    array_set(array2, 1, object_integer(2));
    array_set(array2, 2, object_integer(3));

    Object* array3 = make_array(3);
    array_set(array3, 0, object_integer(4));
    array_set(array3, 1, object_integer(5));
    array_set(array3, 2, object_integer(6));

    long x = object_hash_code(array1);
    long y = object_hash_code(array2);
    long z = object_hash_code(array3);

    assert(x == y);
    assert(x != z);
}

void test_map_hash() {
    Object* map1 = make_map();
    map_set(map1, object_string("a"), object_integer(1));
    map_set(map1, object_string("b"), object_integer(2));

    Object* map2 = make_map();
    map_set(map2, object_string("a"), object_integer(1));
    map_set(map2, object_string("b"), object_integer(2));

    Object* map3 = make_map();
    map_set(map3, object_string("c"), object_integer(3));
    map_set(map3, object_string("d"), object_integer(4));

    long x = object_hash_code(map1);
    long y = object_hash_code(map2);
    long z = object_hash_code(map3);

    assert(x == y);
    assert(x != z);
}

int main() {
  test_string_hash();
  test_symbol_hash();
  test_bool_hash();
  test_int_hash();
  test_float_hash();
  test_char_hash();
  test_list_hash();
  test_pair_hash();
  test_array_hash();
  test_map_hash();

  return EXIT_SUCCESS;
}
