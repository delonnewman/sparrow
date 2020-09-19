#include <stdio.h>
#include <stdlib.h>

#define TYPE_INT    0
#define TYPE_FLOAT  1
#define TYPE_CHAR   2
#define TYPE_STRING 3
#define TYPE_SYMBOL 4
#define TYPE_CONS   5

typedef struct Object {
    int   type;
    void* value;
} Object;

Object object(int type, void* value) {
    Object *object = malloc(sizeof(Object));
    object->type  = type;
    object->value = value;

    return *object;
}

Object integer_object(int x) {
    printf("Integer: %d\n", x);
    return object(TYPE_INT, &x);
}

Object float_object(double x) {
    return object(TYPE_FLOAT, &x); 
}

Object char_object(char x) {
    return object(TYPE_CHAR, &x);
}

Object string_object(char* x) {
    return object(TYPE_STRING, &x);
}

Object symbol_object(char* x) {
    return object(TYPE_SYMBOL, &x);
}

typedef struct Cons {
    Object* car;
    struct Object* cdr;
} Cons;

Object cons(Object* x, Object* xs) {
    Cons *cell = malloc(sizeof(Cons));
    cell->car = x;
    cell->cdr = xs;

    return object(TYPE_CONS, cell);
}

// TODO: Add error handling
Object* first(Object* xs) {
    Cons* cell = xs->value;
    if (xs)
        return cell->car;
    return NULL;
}

Object* next(Object *xs) {
    Cons* cell = xs->value;
    return cell->cdr;
}

void print_float(Object object) {
    double x = *((double*)(object.value));
    printf("%f", x);
}

void print_char(Object object) {
    char x = *((char *)(object.value));
    printf("%c", x);
}

void print_integer(Object object) {
    int x = *((int*)(object.value));
    printf("%d", x);
}

void print(Object object) {
    switch(object.type) {
        case TYPE_INT:
            print_integer(object);
            break;
        case TYPE_FLOAT:
            print_float(object);
            break;
        case TYPE_CHAR:
            print_char(object);
            break;
        default:
            puts("Error: Unknown object");
            exit(0);
    }
}

void destroy_object(Object *object) {
    if (object) {
        free(object);
        if (object->type == TYPE_CONS)
            destroy_object(next(object));
    }
}

int main(int argc, char* argv[]) {
    Object obj = integer_object(1);
    print_integer(obj);
    //printf("\n");
    //print(float_object(0.9));

    return 0;
}