#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define IS_OBJECT(O) (O != NULL && O->sp_obj == true)
#define TYPE_TAG_IS(O, T) (O->type == T)
#define IS_TYPE(O, T) IS_OBJECT(O) && TYPE_TAG_IS(O, T)

enum {
  TYPE_NULL,
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_BOOL,
  TYPE_CHAR,
  TYPE_STRING,
  TYPE_SYMBOL,
  TYPE_CONS,
  TYPE_ARRAY,
  TYPE_MAP,
};

typedef struct Object {
  bool sp_obj;
  int type;
  long int_val;
  double float_val;
  char char_val;

  // strings, symbols
  char* str_val;

  // collections
  size_t count;

  // arrays
  struct Object** array_ref;

  // dynamic objects and lists
  struct Object* ref;
  struct Object* next;
} Object;

Object* object_allocate();
void object_destroy(Object* object);
void object_copy(Object* target, Object* source);

Object* object_null();
Object* object_integer(long value);
Object* object_char(char value);
Object* object_float(double value);
Object* object_string(char* value);
Object* object_symbol(char* value);
Object* object_true();
Object* object_false();

Object* list_empty();
Object* list_cons(Object* value, Object* list);
Object* list_first(Object* list);
Object* list_next(Object* list);
void list_print(Object* list);
bool is_list(Object* list);

Object* make_array(size_t size);
Object* array_at(Object* array, size_t index);
void array_set(Object* array, size_t index, Object* value);
void array_print(Object* array);
bool is_array(Object* array);

size_t count(Object* list);
bool is_collection(Object* list);

bool is_object(Object* obj);
bool is_null(Object* obj);
bool is_equal(Object* obj1, Object* obj2);
bool is_zero(Object* obj);
bool is_empty(Object* list);
bool is_false(Object* obj);
bool is_true(Object* obj);
bool is_bool(Object* obj);
bool is_integer(Object* obj);
bool is_float(Object* obj);
bool is_number(Object* obj);

// Native to object conversions
bool bool_to_int(Object* obj);
Object* int_to_bool(bool);

char* type_name(Object* obj);
void print(Object* obj);
void say(Object* obj);
