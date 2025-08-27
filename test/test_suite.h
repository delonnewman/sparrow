#include "sparrow.h"
#include <assert.h>

#define SKIP(x) NULL

void assert_is_not_null(Object* obj);
void assert_is_not_bool(Object* obj);
void assert_is_not_text(Object* obj);
void assert_is_not_number(Object* obj);
void assert_is_not_coll(Object* obj);
