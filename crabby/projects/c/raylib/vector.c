// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +                                                                                                   +
// +                       Vector from C++ in C. Use with caution...unknown                            +
// +                                                                                                   +
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

static const int DEFAULT_CAPACITY = 4;

typedef struct vector_t {
    int* elements;
    int capacity;
    int size;
} vector_t;

vector_t* vector_new()
{
    return (vector_t*) malloc(sizeof(vector_t));
}

void vector_ctr(vector_t* obj)
{
    obj->elements = calloc(DEFAULT_CAPACITY, sizeof(int));
    obj->capacity = DEFAULT_CAPACITY;
    obj->size = 0;
}

void vector_dtr(vector_t* obj)
{
    free(obj->elements);
    free(obj);
}

int vector_size(vector_t* obj)
{
    return obj->size;
}

int vector_capacity(vector_t* obj)
{
    return obj->capacity;
}

void vector_push_back(struct vector_t* obj, const int element)
{
    if(obj->size > 0 && obj->size % obj->capacity == 0) {    /* Vector is full */
        obj->capacity = (obj->size / DEFAULT_CAPACITY + 1) * DEFAULT_CAPACITY; /* Increase in Steps of DEFAULT_CAPACITY */
        obj->elements = realloc(obj->elements, obj->capacity * sizeof(int));
        printf("New Allocation: %d\n", obj->capacity);
    }
    obj->elements[obj->size++] = element;
}

int vector_at(vector_t* obj, const int index)
{
    return obj->elements[index];
}

int* vector_begin(vector_t* obj)
{
    return &obj->elements[0];
}

int* vector_end(vector_t* obj)
{
    /* Returns a THEORETICAL past-the-end Element 
        and thus shall not be dereferenced! */
    return &obj->elements[obj->size];
}







