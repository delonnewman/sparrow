#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

char* type_name(Object* obj);

Object* object_allocate();
void object_destroy(Object* object);
Object* object_new_integer(long value);
Object* object_new_float(double value);
Object* object_new_string(char* value);
Object* object_new_symbol(char* value);
void object_copy(Object* target, Object* source);

bool list_is_empty(Object* xs);
Object* list_empty();
Object* list_cons(Object* x, Object* xs);
Object* list_car(Object* xs);
Object* list_cdr(Object* xs);
Object* list_count(Object* xs);
void list_print(Object* xs);

void print(Object *obj);
