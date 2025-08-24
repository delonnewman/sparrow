#include "sparrow.h"

Object* object_allocate() {
  Object* object = malloc(sizeof(Object));
  object->type   = TYPE_VOID;
  object->ref    = NULL;
  object->next   = NULL;
  object->length = -1;
  return object;
}

void object_destroy(Object *object) {
  object->ref = NULL;
  switch(object->type) {
  case TYPE_BOOL:
  case TYPE_NULL:
    // ignore singletons
    break;
  case TYPE_INT:
  case TYPE_FLOAT:
    free(object);
    break;
  case TYPE_STRING:
  case TYPE_SYMBOL:
    free(object);
    break;
  case TYPE_CONS:
    free(object);
    object_destroy(list_next(object));
    break;
  default:
    fprintf(stderr, "TypeError: invalid type");
    exit(0);
  }
}

Object* OBJECT_NULL = NULL;

Object* object_null() {
  if (OBJECT_NULL != NULL) {
    return OBJECT_NULL;
  }

  Object* object  = object_allocate();
  object->type    = TYPE_NULL;
  object->ref     = NULL;
  object->length  = 0;

  OBJECT_NULL = object;

  return object;
}

bool is_object(Object* obj) {
 return IS_OBJECT(obj);
}

bool is_null(Object* obj) {
  return IS_TYPE(obj, TYPE_NULL);
}

Object* object_integer(Int value) {
  Object* object = object_allocate();
  object->type   = TYPE_INT;
  object->ref    = &value;

  return object;
}

Object* object_char(Char value) {
  Object* object = object_allocate();
  object->type   = TYPE_CHAR;
  object->ref    = &value;

  return object;
}

Object* object_float(Float value) {
  Object* object = object_allocate();
  object->type   = TYPE_FLOAT;
  object->ref    = &value;

  return object;
}

Object* object_string(Str value) {
  Object* object  = object_allocate();
  object->type    = TYPE_STRING;
  object->length  = strlen(value);
  object->ref     = malloc(strlen(value) + 1);

  strcpy(object->ref, value);

  return object;
}

Object* object_symbol(Str value) {
  Object* object = object_allocate();
  object->type   = TYPE_SYMBOL;
  object->ref    = malloc(strlen(value) + 1);

  strcpy(object->ref, value);

  return object;
}

Object* BOOL_TRUE = NULL;
Bool True = 1;

Object* object_true() {
  if (BOOL_TRUE != NULL) {
    return BOOL_TRUE;
  }

  Object* object  = object_allocate();
  object->type    = TYPE_BOOL;
  object->ref     = &True;

  BOOL_TRUE = object;

  return object;
}

Object* BOOL_FALSE = NULL;
Bool False = 0;

Object* object_false() {
  if (BOOL_FALSE != NULL) {
    return BOOL_FALSE;
  }

  Object* object  = object_allocate();
  object->type    = TYPE_BOOL;
  object->ref     = &False;

  BOOL_FALSE = object;

  return object;
}

void object_copy(Object* target, Object* source) {
  Float float_copy;
  Int int_copy;
  Char char_copy;
  Str str_data;

  Ref ref = source->ref;

  target->type = source->type;

  switch (source->type) {
  case TYPE_BOOL:
  case TYPE_NULL:
  case TYPE_ARRAY:
  case TYPE_MAP:
    target = source;
    break;
  case TYPE_INT:
    int_copy = *((Int*)ref);
    target->ref = &int_copy;
    break;
  case TYPE_FLOAT:
    float_copy = *((Float*)ref);
    target->ref = &float_copy;
    break;
  case TYPE_CHAR:
    char_copy = *((Char*)ref);
    target->ref = &char_copy;
    break;
  case TYPE_STRING:
  case TYPE_SYMBOL:
    str_data = (Str)ref;
    target->ref = malloc(strlen(str_data) + 1);
    strcpy(target->ref, str_data);
    break;
  case TYPE_CONS:
    target->length = source->length;
    target->ref    = source->ref;
    target->next   = source->next;
    break;
  default:
    fprintf(stderr, "TypeError: unknown type '%s'", type_name(source));
    exit(0);
  }
}

Object* EMPTY = NULL;

Object* list_empty() {
  if (EMPTY != NULL) {
    return EMPTY;
  }

  Object* obj = object_allocate();
  obj->type   = TYPE_CONS;
  obj->ref    = NULL;
  obj->next   = NULL;
  obj->length = 0;

  EMPTY = obj;

  return obj;
}

Object* make_pair(Object* first, Object* second) {
  Object* obj = object_allocate();
  obj->type   = TYPE_CONS;
  obj->ref    = first;
  obj->next   = second;
  obj->length = -1;

  return obj;
}

Object* pair_key(Object* pair) {
  if (!is_pair(pair)) {
    fprintf(stderr, "TypeError: invalid operation on %s, 'key'", type_name(pair));
    exit(0);
  }
  return pair->ref;
}

Object* pair_value(Object* pair) {
  if (!is_pair(pair)) {
    fprintf(stderr, "TypeError: invalid operation on %s, 'value'", type_name(pair));
    exit(0);
  }
  return pair->next;
}

Object* list_cons(Object* value, Object* list) {
  if (IS_TYPE(list, TYPE_NULL)) {
    list = list_empty();
  }

  if (IS_TYPE(list, TYPE_CONS) == false) {
    fprintf(stderr, "TypeError: cannot cons type: %s", type_name(list));
    exit(0);
  }

  Object* obj = object_allocate();
  obj->type   = TYPE_CONS;
  obj->ref    = value;
  obj->next   = list;
  obj->length = list->length + 1;

  return obj;
}

Object* list_first(Object* list) {
  if (IS_TYPE(list, TYPE_CONS) == false) {
    fprintf(stderr, "TypeError: cannot get the first element of a %s", type_name(list));
    exit(0);
  }

  Object* value = list->ref;
  if (value == NULL) {
    return object_null();
  }

  return value;
}

Object* list_next(Object *list) {
  if (IS_TYPE(list, TYPE_CONS) == false) {
    fprintf(stderr, "TypeError: cannot get the next of a %s", type_name(list));
    exit(0);
  }

  Object* value = list->next;
  if (value == NULL) {
    return object_null();
  }

  return value;
}

void list_print(Object* list) {
  putchar('(');

  Object* current = list;

  while (!is_empty(current)) {
    print(current->ref);
    if (!is_empty(current->next)) {
      putchar(' ');
    }
    current = current->next;
  }
  
  putchar(')');
}

Bool is_cons(Object* list) {
  return IS_TYPE(list, TYPE_CONS);
}

Bool is_pair(Object* list) {
  return (IS_TYPE(list, TYPE_CONS)) && list->length == -1;
}

Bool is_list(Object* list) {
  return (IS_TYPE(list, TYPE_CONS)) && list->length != -1;
}

Str type_name(Object* obj) {
  switch (obj->type) {
  case TYPE_INT:
    return "Num[Int]";
  case TYPE_FLOAT:
    return "Num[Float]";
  case TYPE_BOOL:
    return "Bool";
  case TYPE_CHAR:
    return "Char";
  case TYPE_STRING:
    return "Str";
  case TYPE_SYMBOL:
    return "Sym";
  case TYPE_CONS:
    return "Cons";
  case TYPE_NULL:
    return "Null";
  case TYPE_MAP:
    return "Map";
  case TYPE_ARRAY:
    return "Array";
  default:
    fprintf(stderr, "TypeError: unknown type code '%d'\n", obj->type);
    exit(0);
  }
}

Bool is_bool(Object *obj) {
  return IS_TYPE(obj, TYPE_BOOL);
}

Bool is_false(Object *obj) {
  return IS_OBJECT(obj) &&
    (TYPE_TAG_IS(obj, TYPE_NULL) || (TYPE_TAG_IS(obj, TYPE_BOOL) && obj->ref == &False));
}

Bool is_true(Object *obj) {
  return IS_TYPE(obj, TYPE_BOOL) && obj->ref == &True;
}

Bool bool_to_int(Object* obj) {
  if (!is_bool(obj)) {
    fprintf(stderr, "TypeError: invalid operation on %s", type_name(obj));
    exit(0);
  }

  if (is_true(obj)) {
    return 1;
  }

  return 0;
}

Object* int_to_bool(Bool value) {
  if (value) {
    return object_true();
  }

  return object_false();
}

void object_dump(Object* obj) {
  fprintf(stderr, "#<%s>\n", type_name(obj));
}

Object* make_array(Nat size) {
  Object* object  = object_allocate();
  object->type    = TYPE_ARRAY;

  Object* array[size];
  object->ref    = array;
  object->length = size;

  return object;
}

void array_set(Object *array, Nat index, Object* value) {
  if (!is_array(array)) {
    fprintf(stderr, "TypeError: invalid operation on %s, 'set'", type_name(array));
    exit(0);
  }

  if (index >= (size_t)array->length) {
    fprintf(stderr, "TypeError: out of bounds index for an array with a length of %ld", array->length);
    exit(0);
  }

  Object** storage = (Object**)array->ref;
  storage[index] = value;
}

Object* array_at(Object* array, Nat index) {
  if (!is_array(array)) {
    fprintf(stderr, "TypeError: invalid operation on %s, 'at'", type_name(array));
    exit(0);
  }

  if (index >= (size_t)array->length) {
    return object_null();
  }

  Object** storage = (Object**)array->ref;
  return storage[index];
}

void array_print(Object* array) {
  printf("[");
  for (long i = 0; i < array->length; i++) {
    print(array_at(array, i));
    if (i < (array->length - 1)) {
      printf(", ");
    }
  }
  printf("]");
}

Bool array_is_equal(Object* this, Object* other) {
  if (this->length != other->length) {
    return false;
  }

  bool result = true;
  for (long i = 0; i < this->length; i++) {
    result = result && is_equal(array_at(this, i), array_at(other, i));
  }
  return result;
}

Bool is_array(Object* array) {
  return IS_TYPE(array, TYPE_ARRAY);
}

#define MAP_BUCKET_COUNT 10

Object* make_map() {
  Object* map = make_array(MAP_BUCKET_COUNT);
  for (long i = 0; i < MAP_BUCKET_COUNT; i++) {
    array_set(map, i, list_empty());
  }
  map->length = 0;
  map->type = TYPE_MAP;
  return map;
}

void map_set(Object* map, Object* key, Object* value) {
  printf("Setting map key: ");
  print(key); printf(" => "); say(value);

  long key_hash = object_hash_code(key);
  printf("Key hash: %ld\n", key_hash);

  size_t index = key_hash % MAP_BUCKET_COUNT;
  printf("Storage index: %zu\n", index);

  Object** storage = (Object**)map->ref;
  Object* bucket = storage[index];
  assert(is_list(bucket));
  printf("Bucket: ");
  say(bucket);

  Object* pair = make_pair(key, value);
  map_set_bucket(map, key, list_cons(pair, bucket));
  map->length += 1;
}

Object* map_get_bucket(Object* map, Object* key) {
  long key_hash = object_hash_code(key);
  printf("Key hash: %ld\n", key_hash);

  size_t index = key_hash % MAP_BUCKET_COUNT;
  printf("Storage index: %zu\n", index);

  Object** storage = (Object**)map->ref;
  assert(is_list(storage[index]));
  return storage[index];
}

void map_set_bucket(Object* map, Object* key, Object* bucket) {
  long key_hash = object_hash_code(key);
  size_t index = key_hash % MAP_BUCKET_COUNT;

  assert(is_list(bucket));
  Object** storage = (Object**)map->ref;
  storage[index] = bucket;
}

Object* map_get(Object* map, Object* key) {
  long key_hash = object_hash_code(key);
  size_t index  = key_hash % MAP_BUCKET_COUNT;
  Object** storage = (Object**)map->ref;
  Object* bucket = storage[index];

  Object* pair;
  while (IS_TYPE(bucket, TYPE_NULL)) {
    pair = list_first(bucket);
    if (is_equal(pair_key(pair), key)) {
      return pair_value(pair);
    }
    bucket = list_next(bucket);
  }

  return object_null();
}

Bool is_map(Object* map) {
  return IS_TYPE(map, TYPE_MAP);
}

Bool is_collection(Object* obj) {
  return is_array(obj) || is_list(obj);
}

Bool is_countable(Object* obj) {
  return is_null(obj) || is_collection(obj);
}

Nat collection_count(Object *col) {
  if (!is_countable(col)) {
    fprintf(stderr, "TypeError: cannot get the count of a %s", type_name(col));
    exit(0);
  }

  return col->length;
}

Bool is_empty(Object* list) {
  return collection_count(list) == 0;
}

void print(Object* obj) {
  if (IS_OBJECT(obj) == false) {
    fprintf(stderr, "TypeError: only objects can be printed\n");
    exit(0);
  }

  switch(obj->type) {
  case TYPE_INT:
    printf("%ld", *((Int*)obj->ref));
    break;
  case TYPE_FLOAT:
    printf("%f:%s", *((Float*)obj->ref), type_name(obj));
    break;
  case TYPE_BOOL:
    if (is_true(obj)) {
      printf("true");
    } else {
      printf("false");
    }
    break;
  case TYPE_STRING:
    printf("\"%s\"", (Str)obj->ref);
    break;
  case TYPE_CHAR:
    printf("\%c", *((Char*)obj->ref));
    break;
  case TYPE_SYMBOL:
    printf("'%s", (Str)obj->ref);
    break;
  case TYPE_NULL:
    printf("null");
    break;
  case TYPE_ARRAY:
    array_print(obj);
  case TYPE_MAP:
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

Bool is_zero(Object* number) {
  if (number == NULL) return false;

  switch(number->type) {
    case TYPE_INT:
      return *((Int*)number->ref) == 0;
    case TYPE_FLOAT:
      return *((Float*)number->ref) == 0.0;
    default:
      fprintf(stderr, "TypeError: zero? only works on numeric types");
      exit(0);
  }
}

Bool is_integer(Object* obj) {
  return IS_TYPE(obj, TYPE_INT);
}

Bool is_float(Object* obj) {
  return IS_TYPE(obj, TYPE_FLOAT);
}

Bool is_number(Object* obj) {
  return (IS_TYPE(obj, TYPE_INT)) || (IS_TYPE(obj, TYPE_FLOAT));
}

Bool list_is_equal(Object* list1, Object* list2) {
  bool empty1 = is_empty(list1);
  bool empty2 = is_empty(list2);
  if (empty1 && empty2) return true;
  if (empty1 || empty2) return false;

  Object* current1 = list1;
  Object* current2 = list2;

  while (!is_empty(current1) && !is_empty(current2)) {
    if (!is_equal(current1->ref, current2->ref)) return false;
    current1 = current1->next;
    current2 = current2->next;
  }

  return true;
}

Bool is_equal(Object* object1, Object* object2) {
  if (IS_OBJECT(object1) == false || IS_OBJECT(object2) == false) {
    fprintf(stderr, "TypeError: only objects support equality\n");
    exit(0);
  }

  if (object1->type == object2->type) {
    switch (object1->type) {
      case TYPE_NULL:
        return true;
      case TYPE_INT:
      case TYPE_BOOL:
        return *((Bool*)object1->ref) == *((Bool*)object2->ref);
      case TYPE_FLOAT:
        return *((Float*)object1->ref) == *((Float*)object2->ref);
      case TYPE_CHAR:
        return *((Char*)object1->ref) == *((Char*)object2->ref);
      case TYPE_STRING:
      case TYPE_SYMBOL:
        return strcmp((Str)object1->ref, (Str)object2->ref) == 0;
      case TYPE_CONS:
        return list_is_equal(object1, object2);
      case TYPE_ARRAY:
        return array_is_equal(object1, object2);
      default:
        fprintf(stderr, "TypeError: unknown type '%s'\n", type_name(object1));
        exit(0);
    }
  }
  else if (is_number(object1) && is_number(object2)) {
    if (is_integer(object1)) {
      return *((Int*)object1->ref) == *((Float*)object2->ref);
    }
    if (is_float(object1)) {
      return *((Float*)object1->ref) == *((Int*)object2->ref);
    }
  }

  return false;
}

Int object_hash_code(Object* obj) {
  switch (obj->type) {
  case TYPE_SYMBOL:
  case TYPE_STRING:
    return string_hash((Str)obj->ref, obj->length);
  default:
    fprintf(stderr, "TypeError: unknown hash code type '%s'\n", type_name(obj));
    exit(0);
  }
}

Int hash_combine(long seed, long hash) {
  // a la boost, a la clojure
  seed ^= hash + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  return seed;
}

Int string_hash(const Str string, size_t strlen) {
  long code = 0;
  for (size_t i = 0; i < strlen; i++) {
    for (int j = strlen; j > 0; j--) {
      code += powl(string[i], j);
    }
  }
  return code;
}
