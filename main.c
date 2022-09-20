#include <stdio.h>
#include <stdlib.h>

enum {
    TYPE_INT    = 0,
    TYPE_FLOAT  = 1,
    TYPE_CHAR   = 2,
    TYPE_STRING = 3,
    TYPE_SYMBOL = 4,
    TYPE_CONS   = 5,
};

typedef struct {
    int   type;
    void* value;
} obj_t;

obj_t* object(int type, void* value) {
    obj_t* object = malloc(sizeof(obj_t));
    object->type  = type;
    object->value = value;

    return object;
}

obj_t* integer_object(int x) {
    return object(TYPE_INT, &x);
}

obj_t* float_object(double x) {
    return object(TYPE_FLOAT, &x); 
}

obj_t* char_object(char x) {
    return object(TYPE_CHAR, &x);
}

obj_t* string_object(char* x) {
    return object(TYPE_STRING, &x);
}

obj_t* symbol_object(char* x) {
    return object(TYPE_SYMBOL, &x);
}

/*
typedef struct {
    obj_t* car;
    struct obj_t* cdr;
} Cons;

obj_t cons(obj_t* x, obj_t* xs) {
    Cons *cell = malloc(sizeof(Cons));
    cell->car = x;
    cell->cdr = xs;

    return object(TYPE_CONS, cell);
}

// TODO: Add error handling
obj_t* first(obj_t* xs) {
    Cons* cell = xs->value;
    if (xs)
        return cell->car;
    return NULL;
}

obj_t* next(obj_t *xs) {
    Cons* cell = xs->value;
    return cell->cdr;
}
*/

void print_float(obj_t* obj) {
    printf("%f", *((double*)obj->value));
}

void print_char(obj_t* obj) {
    printf("%c", *((char*)obj->value));
}

void print_integer(obj_t* obj) {
    printf("%d", *((int*)obj->value));
}

void print_string(obj_t* obj) {
    printf("\"%s\"", *((char**)obj->value));
}

void print(obj_t* obj) {
  switch(obj->type) {
        case TYPE_INT:
            puts("int");
            print_integer(obj);
            break;
        case TYPE_FLOAT:
            puts("float");
            print_float(obj);
            break;
        case TYPE_CHAR:
            puts("char");
            print_char(obj);
            break;
        case TYPE_STRING:
            puts("string");
            print_string(obj);
            break;
        default:
            puts("Error: Unknown object");
            exit(0);
    }
}

/*
void destroy_object(obj_t *object) {
    if (object) {
        free(object);
        if (object->type == TYPE_CONS)
            destroy_object(next(object));
    }
}
*/

int main(int argc, char* argv[]) {
    obj_t* obj = integer_object(14);
    obj_t* str = string_object("Testing");
    printf("%d %s", str->type, *((char**)str->value));
    puts("\n");
    print(str);
    puts("\n");
    printf("%d %d", obj->type, *((int*)obj->value));
    puts("\n");
    print_integer(obj);
    puts("\n");
    print(obj);
    //print(&obj);
    //printf("\n");
    //print(float_object(0.9));

    return EXIT_SUCCESS;
}
