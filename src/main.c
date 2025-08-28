#include "sparrow.h"

int main() {
  say(list_empty());

  Object* num = object_float(1.235);
  say(num);

  char* buffer = malloc(sizeof(char) * 100);
  object_inspect(buffer, num);
  puts(buffer);

  Object* obj = list_cons(
    object_float(1.1),
    list_cons(object_char('a'),
              list_cons(object_true(),
                        list_cons(object_integer(2),
                                  list_cons(object_integer(1), list_empty())))));
  say(obj);

  Object* list1 = list_cons(object_integer(1), list_empty());
  Object* list2 = list_cons(object_integer(2), list_empty());

  say(list_cons(list1, list2));

  Object* array = make_array(3);
  array_set(array, 0, object_integer(1));
  array_set(array, 2, object_integer(2));
  say(array);

  Object* map = make_map();
  map_set(map, object_string("a"), object_float(3.4));
  say(map);

  return EXIT_SUCCESS;
}
