#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    char **items; // Pointer to dynamically allocated array of char*
    size_t size;  // Capacity of the array
    size_t len;   // Current number of elements in the array
} dynamic_array_ts;

dynamic_array_ts *dynamic_array_new(size_t initial_size);

void dynamic_array_destroy(dynamic_array_ts *dynamic_array);

void dynamic_array_free(dynamic_array_ts **dynamic_array);

unsigned dynamic_array_append(dynamic_array_ts *dynamic_array, char *line);

char *dynamic_array_pop(dynamic_array_ts *dynamic_array);

#endif
