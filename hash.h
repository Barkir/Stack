#ifndef HASH_H
#define HASH_H

#include "stack.h"

void DoHash(void * data, size_t size, int * hash);
static int HASH = 5381;

#endif
