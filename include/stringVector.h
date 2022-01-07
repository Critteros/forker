#pragma once
#include <stdlib.h>
#include <string.h>

typedef struct
{
    size_t size;
    size_t capacity;
    char **data;
} stringVector;

stringVector *createStringVector(void);
void appendStringVector(stringVector *vec, const char *el);
size_t getSizeStringVector(stringVector *vec);
void deleteStringVector(stringVector *vec);