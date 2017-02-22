#include "DynamicArray.h"
#include <stdlib.h>

DynamicArray* DynamicArray_create(void) {
     DynamicArray *a = malloc(sizeof(*a));
     a->count = 0;
     a->items = NULL;
     a->size = DynamicArray_initSize;
     return a;
}

void DynamicArray_free(DynamicArray *a) {
     free(a);
}
