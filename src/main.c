#include "lisp.h"

int main() {
  Object* obj = list_cons(object_new_integer(2), list_cons(object_new_integer(1), list_empty()));
  print(obj);

  return EXIT_SUCCESS;
}
