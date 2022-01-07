#include "stringVector.h"

stringVector *createStringVector(void)
{
    stringVector *vec = calloc(1, sizeof(stringVector));
    vec->size = 0;

    vec->data = calloc(1, sizeof(char *));
    vec->capacity = 1;

    return vec;
}

void deleteStringVector(stringVector *vec)
{
    for (unsigned i = 0; i < vec->size; i++)
    {
        free(vec->data[i]);
    }
    free(vec->data);

    free(vec);
}

void appendStringVector(stringVector *vec, const char *el)
{
    const size_t futureSize = vec->size + 1;

    //Resize
    if (futureSize > vec->capacity)
    {
        vec->data = realloc(vec->data, futureSize * sizeof(char *));
        vec->capacity = futureSize;
    }

    vec->data[vec->size] = calloc(strlen(el) + 1, sizeof(char));
    strcpy(vec->data[vec->size], el);

    vec->size += 1;
}
size_t getSizeStringVector(stringVector *vec)
{
    return vec->size;
}
