#include <stdio.h>

#include "hash.h"

void DoHash(void * data, size_t size, int * hash)
{
    *hash = 5381;
    unsigned char * todo = (unsigned char *) data;
    for (int i = 0; i < size; i++)
    {
        *hash += todo[i];
    }
}
