#include "lisp.h"

char* type_name(Object* obj) {
  switch (obj->type) {
  case TYPE_INT:
    return "integer";
  case TYPE_FLOAT:
    return "float";
  case TYPE_CHAR:
    return "char";
  case TYPE_STRING:
    return "string";
  case TYPE_SYMBOL:
    return "symbol";
  case TYPE_CONS:
    return "list";
  default:
    puts("Error: Unknown type");
    exit(0);
  }
}

Object* object_allocate() {
  Object* object = malloc(sizeof(Object));
  return object;
}

void object_destroy(Object *object) {
  switch(object->type) {
  case TYPE_INT:
  case TYPE_FLOAT:
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
    puts("TypeError: invalid type");
    exit(0);
  }
}

Object* object_new_integer(long value) {
  Object* object  = object_allocate();
  object->type    = TYPE_INT;
  object->int_val = value;

  return object;
}

Object* object_new_float(double value) {
  Object* object    = object_allocate();
  object->type      = TYPE_FLOAT;
  object->float_val = value;

  return object;
}

Object* object_new_string(char* value) {
  Object* object  = object_allocate();
  object->type    = TYPE_STRING;
  object->str_val = malloc(strlen(value) + 1);
  strcpy(object->str_val, value);

  return object;
}

Object* object_new_symbol(char* value) {
  Object* object  = object_allocate();
  object->type    = TYPE_SYMBOL;
  object->str_val = malloc(strlen(value) + 1);
  strcpy(object->str_val, value);

  return object;
}

void object_copy(Object* target, Object* source) {
  target->type = source->type;

  switch (source->type) {
  case TYPE_INT:
    target->int_val = source->int_val;
    break;
  case TYPE_FLOAT:
    target->float_val = source->float_val;
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
  default:
    puts("Error: Unknown type");
    exit(0);
  }
}

bool list_is_empty(Object* list) {
  if (list->type != TYPE_CONS) {
    printf("TypeError: can only determine if lists are empty got %s instead", type_name(list));
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
    printf("TypeError: cannot cons type: %s", type_name(list));
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
    printf("TypeError: cannot get the car of a %s", type_name(list));
    exit(0);
  }

  return list->car;
}

Object* list_cdr(Object *list) {
  if (list->type != TYPE_CONS) {
    printf("TypeError: cannot get the cdr of a %s", type_name(list));
    exit(0);
  }

  return list->cdr;
}

Object* list_count(Object *list) {
  if (list->type != TYPE_CONS) {
    printf("TypeError: cannot get the count of a %s", type_name(list));
    exit(0);
  }

  return object_new_integer(list->count);
}

void list_print(Object* list) {
  putchar('(');

  Object* current = list;
  
  while (!list_is_empty(current)) {
    print(current->car);
    if (!list_is_empty(current->cdr)) {
      putchar(' ');
    }
    current = current->cdr;
  }
  
  putchar(')');
}

void print(Object* obj) {
  switch(obj->type) {
  case TYPE_INT:
    printf("%ld", obj->int_val);
    break;
  case TYPE_FLOAT:
    printf("%f", obj->float_val);
    break;
  case TYPE_STRING:
    printf("\"%s\"", obj->str_val);
    break;
  case TYPE_SYMBOL:
    printf("%s", obj->str_val);
    break;
  case TYPE_CONS:
    list_print(obj);
    break;
  default:
    puts("Error: Unknown type");
    exit(0);
  }
}
