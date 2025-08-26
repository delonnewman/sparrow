#include "sparrow.h"

int main() {
  say(list_empty());

  Object* num = object_float(1.235);
  say(num);

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

  return EXIT_SUCCESS;
}
