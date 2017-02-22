#ifndef H_DYNAMICARRAY
#define H_DYNAMICARRAY

static const int DynamicArray_initSize = 100;

typedef struct DynamicArray_s DynamicArray;
struct DynamicArray_s {
     int count;
     int size;
     void *items;
};

DynamicArray* DynamicArray_create(void);
void DynamicArray_free(DynamicArray *a);

#endif
