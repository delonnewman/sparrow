#include "lisp.h"

int die(char* type, char* message) {
  fprintf(stderr, "%s: '%s'\n", type, message);
  exit(0);
}

Object* object_allocate() {
  Object* object = malloc(sizeof(Object));
  return object;
}

void object_destroy(Object *object) {
  switch(object->type) {
  case TYPE_INT:
  case TYPE_FLOAT:
  case TYPE_BOOL:
    free(object);
    break;
  case TYPE_STRING:
  case TYPE_SYMBOL:
    free(object);
    free(object->str_val);
    break;
  case TYPE_CONS:
    free(object);
    object_destroy(list_cdr(object));
    break;
  default:
    fprintf(stderr, "TypeError: invalid type");
    exit(0);
  }
}

Object* object_integer(long value) {
  Object* object  = object_allocate();
  object->type    = TYPE_INT;
  object->int_val = value;

  return object;
}

Object* object_char(char value) {
  Object* object  = object_allocate();
  object->type    = TYPE_CHAR;
  object->char_val = value;

  return object;
}

Object* object_float(double value) {
  Object* object    = object_allocate();
  object->type      = TYPE_FLOAT;
  object->float_val = value;

  return object;
}

Object* object_string(char* value) {
  Object* object  = object_allocate();
  object->type    = TYPE_STRING;
  object->str_val = malloc(strlen(value) + 1);
  strcpy(object->str_val, value);

  return object;
}

Object* object_symbol(char* value) {
  Object* object  = object_allocate();
  object->type    = TYPE_SYMBOL;
  object->str_val = malloc(strlen(value) + 1);
  strcpy(object->str_val, value);

  return object;
}

Object* BOOL_TRUE = NULL;

Object* object_true() {
  if (BOOL_TRUE != NULL) {
    return BOOL_TRUE;
  }

  Object* object  = object_allocate();
  object->type    = TYPE_BOOL;
  object->int_val = 1;

  BOOL_TRUE = object;

  return object;
}

Object* BOOL_FALSE = NULL;

Object* object_false() {
  if (BOOL_FALSE != NULL) {
    return BOOL_FALSE;
  }

  Object* object  = object_allocate();
  object->type    = TYPE_BOOL;
  object->int_val = 0;

  BOOL_FALSE = object;

  return object;
}

void object_copy(Object* target, Object* source) {
  target->type = source->type;

  switch (source->type) {
  case TYPE_INT:
  case TYPE_BOOL:
    target->int_val = source->int_val;
    break;
  case TYPE_FLOAT:
    target->float_val = source->float_val;
    break;
  case TYPE_CHAR:
    target->char_val = source->char_val;
    break;
  case TYPE_STRING:
  case TYPE_SYMBOL:
    target->str_val = malloc(strlen(source->str_val) + 1);
    strcpy(target->str_val, source->str_val);
    break;
  case TYPE_CONS:
    target->count = source->count;
    target->car   = source->car;
    target->cdr   = source->cdr;
    break;
  default:
    fprintf(stderr, "TypeError: unknown type '%s'", type_name(source));
    exit(0);
  }
}

bool is_zero(Object* number) {
  switch(number->type) {
    case TYPE_INT:
      return number->int_val == 0;
    case TYPE_FLOAT:
      return number->float_val == 0.0;
    default:
      fprintf(stderr, "TypeError: zero? only works on numeric types");
      exit(0);
  }
}

bool is_empty(Object* list) {
  if (list->type != TYPE_CONS) {
    fprintf(stderr, "TypeError: can only determine if lists are empty got %s instead", type_name(list));
    exit(0);
  }

  return list->count == 0;
}

Object* EMPTY = NULL; 

Object* list_empty() {
  if (EMPTY != NULL) {
    return EMPTY;
  }

  Object* obj = malloc(sizeof(Object));
  obj->type   = TYPE_CONS;
  obj->car    = NULL;
  obj->cdr    = NULL;
  obj->count  = 0;

  EMPTY = obj;

  return obj;
}

Object* list_cons(Object* value, Object* list) {
  if (list->type != TYPE_CONS) {
    fprintf(stderr, "TypeError: cannot cons type: %s", type_name(list));
    exit(0);
  }

  Object* obj = object_allocate();
  obj->type = TYPE_CONS;

  obj->car = object_allocate();
  object_copy(obj->car, value);

  obj->cdr = list;
  obj->count = list->count + 1;

  return obj;
}

Object* list_car(Object* list) {
  if (list->type != TYPE_CONS) {
    fprintf(stderr, "TypeError: cannot get the car of a %s", type_name(list));
    exit(0);
  }

  return list->car;
}

Object* list_cdr(Object *list) {
  if (list->type != TYPE_CONS) {
    fprintf(stderr, "TypeError: cannot get the cdr of a %s", type_name(list));
    exit(0);
  }

  return list->cdr;
}

Object* list_count(Object *list) {
  if (list->type != TYPE_CONS) {
    fprintf(stderr, "TypeError: cannot get the count of a %s", type_name(list));
    exit(0);
  }

  return object_integer(list->count);
}

void list_print(Object* list) {
  putchar('(');

  Object* current = list;

  while (!is_empty(current)) {
    print(current->car);
    if (!is_empty(current->cdr)) {
      putchar(' ');
    }
    current = current->cdr;
  }
  
  putchar(')');
}

char* type_name(Object* obj) {
  switch (obj->type) {
  case TYPE_INT:
    return "integer";
  case TYPE_FLOAT:
    return "float";
  case TYPE_BOOL:
    return "boolean";
  case TYPE_CHAR:
    return "char";
  case TYPE_STRING:
    return "string";
  case TYPE_SYMBOL:
    return "symbol";
  case TYPE_CONS:
    return "list";
  default:
    fprintf(stderr, "TypeError: unknown type code '%d'\n", obj->type);
    exit(0);
  }
}

bool is_false(Object *obj) {
  return obj->type == TYPE_BOOL && obj->int_val == 0;
}

bool is_true(Object *obj) {
  return !is_false(obj);
}

void object_dump(Object* obj) {
  fprintf(stderr, "#<%s>\n", type_name(obj));
}

void print(Object* obj) {
  switch(obj->type) {
  case TYPE_INT:
    printf("%ld", obj->int_val);
    break;
  case TYPE_FLOAT:
    printf("%f", obj->float_val);
    break;
  case TYPE_BOOL:
    if (is_false(obj)) printf("%s", "false");
    else printf("%s", "true");
    break;
  case TYPE_STRING:
    printf("\"%s\"", obj->str_val);
    break;
  case TYPE_CHAR:
    printf("\%c", obj->char_val);
    break;
  case TYPE_SYMBOL:
    printf("%s", obj->str_val);
    break;
  case TYPE_CONS:
    list_print(obj);
    break;
  default:
    fprintf(stderr, "TypeError: unknown type '%s'\n", type_name(obj));
    exit(0);
  }
}

void say(Object* obj) {
  print(obj);
  printf("\n");
}

bool list_is_equal(Object* list1, Object* list2) {
  bool empty1 = is_empty(list1);
  bool empty2 = is_empty(list2);
  if (empty1 && empty2) return true;
  if (empty1 || empty2) return false;

  Object* current1 = list1;
  Object* current2 = list2;

  while (!is_empty(current1) && !is_empty(current2)) {
    if (!is_equal(current1->car, current2->car)) return false;
    current1 = current1->cdr;
    current2 = current2->cdr;
  }

  return true;
}

bool is_integer(Object* obj) {
  return obj->type == TYPE_INT;
}

bool is_float(Object* obj) {
  return obj->type == TYPE_FLOAT;
}

bool is_number(Object* obj) {
  return is_integer(obj) || is_float(obj);
}

bool is_equal(Object* object1, Object* object2) {
  if (object1->type == object2->type) {
    switch (object1->type) {
      case TYPE_INT:
      case TYPE_BOOL:
        return object1->int_val == object2->int_val;
      case TYPE_FLOAT:
        return object1->float_val == object2->float_val;
      case TYPE_CHAR:
        return object1->char_val == object2->char_val;
      case TYPE_STRING:
      case TYPE_SYMBOL:
        return strcmp(object1->str_val, object2->str_val) == 0;
      case TYPE_CONS:
        return list_is_equal(object1, object2);
      default:
        fprintf(stderr, "TypeError: unknown type '%s'\n", type_name(object1));
        exit(0);
    }
  }
  else if (is_number(object1) && is_number(object2)) {
    if (is_integer(object1)) {
      return object1->int_val == object2->float_val;
    }
    if (is_float(object1)) {
      return object1->float_val == object2->int_val;
    }
  }

  return false;
}
