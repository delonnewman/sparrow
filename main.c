#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum {
  TYPE_INT    = 0,
  TYPE_FLOAT  = 1,
  TYPE_CHAR   = 2,
  TYPE_STRING = 3,
  TYPE_SYMBOL = 4,
  TYPE_CONS   = 5,
};

typedef struct Object {
  int    type;
  long   int_val;
  double float_val;

  // strings, symbols
  char* str_val;
    
  // list count, car and cdr
  int            count;
  struct Object* car;
  struct Object* cdr;
} Object;


void print(Object* obj);
char* stype(Object* obj);

char* stype(Object* obj) {
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

void copy_value(Object* target, Object* source) {
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

bool list_is_empty(Object* xs) {
  if (xs->type != TYPE_CONS) {
    printf("TypeError: can only determine if lists are empty got %s instead", stype(xs));
    exit(0);
  }

  return xs->count == 0;
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

Object* list_cons(Object* x, Object* xs) {
  if (xs->type != TYPE_CONS) {
    printf("TypeError: cannot cons type: %s", stype(xs));
    exit(0);
  }

  Object* obj = object_allocate();
  obj->type = TYPE_CONS;

  obj->car = object_allocate();
  copy_value(obj->car, x);

  obj->cdr = xs;
  obj->count = xs->count + 1;

  return obj;
}

Object* list_car(Object* xs) {
  if (xs->type != TYPE_CONS) {
    printf("TypeError: cannot get the car of a %s", stype(xs));
    exit(0);
  }

  return xs->car;
}

Object* list_cdr(Object *xs) {
  if (xs->type != TYPE_CONS) {
    printf("TypeError: cannot get the cdr of a %s", stype(xs));
    exit(0);
  }

  return xs->cdr;
}

Object* list_count(Object *xs) {
  if (xs->type != TYPE_CONS) {
    printf("TypeError: cannot get the count of a %s", stype(xs));
    exit(0);
  }

  return object_new_integer(xs->count);
}

void list_print(Object* xs) {
  if (xs->type != TYPE_CONS) {
    printf("TypeError: can only print lists got a %s instead", stype(xs));
    exit(0);
  }

  putchar('(');

  Object* list = xs;
  
  while (!list_is_empty(list)) {
    print(list->car);
    if (!list_is_empty(list->cdr)) {
      putchar(' ');
    }
    list = list->cdr;
  }
  
  putchar(')');
}

void float_print(Object* obj) {
  printf("%f", obj->float_val);
}

void integer_print(Object* obj) {
  printf("%ld", obj->int_val);
}

void string_print(Object* obj) {
  printf("\"%s\"", obj->str_val);
}

void symbol_print(Object* obj) {
  printf("%s", obj->str_val);
}

void print(Object* obj) {
  switch(obj->type) {
  case TYPE_INT:
    integer_print(obj);
    break;
  case TYPE_FLOAT:
    float_print(obj);
    break;
  case TYPE_STRING:
    string_print(obj);
    break;
  case TYPE_SYMBOL:
    symbol_print(obj);
    break;
  case TYPE_CONS:
    list_print(obj);
    break;
  default:
    puts("Error: Unknown type");
    exit(0);
  }
}

void destroy_object(Object *object) {
  if (object) {
    free(object);
    if (object->type == TYPE_CONS) {
      destroy_object(list_cdr(object));
    }
  }
}

int main() {
  Object* obj = list_cons(object_new_integer(2), list_cons(object_new_integer(1), list_empty()));
  print(obj);

  return EXIT_SUCCESS;
}
