#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define IS_OBJECT(O) (O != NULL)
#define TYPE_TAG_IS(O, T) (O->type == T)
#define IS_TYPE(O, T) IS_OBJECT(O) && TYPE_TAG_IS(O, T)

#define INT(O) *((Int*)O->ref)
#define FLOAT(O) *((Float*)O->ref)
#define BOOL(O) *((Bool*)O->ref)
#define CHAR(O) *((Char*)O->ref)
#define STR(O) ((Str)O->ref)

typedef long Int;
typedef size_t Nat;
typedef double Float;
typedef char* Str;
typedef char Char;
typedef bool Bool;
typedef void* Ref;

typedef enum ObjectType {
  TYPE_VOID,
  TYPE_NULL,
  TYPE_BOOL,
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_CHAR,
  TYPE_STRING,
  TYPE_SYMBOL,
  TYPE_CONS,
  TYPE_ARRAY,
  TYPE_MAP,
} ObjectType;

typedef struct Object {
  ObjectType type;
  Int length;
  void* ref;
  struct Object* next;
} Object;

Object* object_allocate();
void object_destroy(Object* object);
void object_copy(Object* target, Object* source);

Object* object_null();
Object* object_integer(Int value);
Object* object_char(Char value);
Object* object_float(Float value);
Object* object_string(Str value);
Object* object_symbol(Str value);
Object* object_true();
Object* object_false();

Object* list_empty();
Object* list_cons(Object* value, Object* list);
Object* list_first(Object* list);
Object* list_next(Object* list);
void list_print(Object* list);
Bool is_cons(Object* cons);
Bool is_list(Object* cons);

Object* make_pair(Object* first, Object* second);
Object* pair_key(Object* pair);
Object* pair_value(Object* pair);
Bool is_pair(Object* cons);

Object* make_array(Nat size);
Object* array_at(Object* array, Nat index);
void array_set(Object* array, Nat index, Object* value);
void array_print(Object* array);
Bool is_array(Object* array);

Object* make_map();
void map_set(Object* map, Object* key, Object* value);
Object* map_get_bucket(Object* map, Object* key);
void map_set_bucket(Object* map, Object* key, Object* bucket);
Object* map_get(Object* map, Object* key);
Object* map_keys(Object* map);
Object* map_values(Object* map);
Object* map_entries(Object* map);
Bool is_map(Object* map);

Nat length(Object* list);
Bool is_coll(Object* list);
Bool is_countable(Object* obj);

Bool is_object(Object* obj);
Bool is_null(Object* obj);
Bool is_equal(Object* obj1, Object* obj2);
Bool is_zero(Object* obj);
Bool is_empty(Object* list);
Bool is_false(Object* obj);
Bool is_true(Object* obj);
Bool is_bool(Object* obj);
Bool is_integer(Object* obj);
Bool is_float(Object* obj);
Bool is_number(Object* obj);
Bool is_char(Object* obj);
Bool is_string(Object* obj);
Bool is_symbol(Object* obj);

Int object_hash_code(Object* obj);
Int string_hash(const Str string, Nat strlen);

// Native to object conversions
Bool bool_to_int(Object* obj);
Object* int_to_bool(Bool);

Str type_name(Object* obj);
void print(Object* obj);
void say(Object* obj);
