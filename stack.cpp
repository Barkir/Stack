#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "stack.h"

int Stack_Ctor(Stack * stk, size_t stk_capacity)
{
    stk->capacity = stk_capacity < 16 ? 16 : stk_capacity;
    stk->size = 0;
    stk->data = (StackEl_t*) calloc(stk->capacity, sizeof(StackEl_t));

    assert(stk->data);
    return OK;
}
int Stack_Dtor(Stack * stk)
{
    stk->capacity = 0;
    stk->size = 0;

    assert(stk->data);
    free(stk->data);
    fprintf(stderr, "Stack Terminated!\n");
    return OK;
}

StackEl_t StackPush(Stack * stk, StackEl_t elem)
{
    if (stk->size >= stk->capacity)
        if(StackExpand(stk) == ERROR) return NAN;

    stk->data[stk->size] = elem;
    stk->size++;
    return elem;
}

StackEl_t StackPop(Stack * stk)
{
    StackEl_t elem = 0;

    if (stk->size < stk->capacity / 4)
        if (StackShrink(stk) == ERROR) return NAN;

    elem = stk->data[stk->size];
    stk->data[stk->size] = 0;
    stk->size--;
    return elem;

}

int StackExpand(Stack * stk)
{
    StackEl_t * check = 0;
    if ((check = (StackEl_t*) realloc(stk->data, (stk->capacity * 2) * sizeof(*(stk->data)))) == NULL)
        return ERROR;

    stk->data = check;
    stk->capacity *= 2;
    return OK;
}

int StackShrink(Stack * stk)
{
    StackEl_t * check = 0;
    if ((check = (StackEl_t*) realloc(stk->data, (stk->capacity / 4) * sizeof(*(stk->data)))) == NULL)
        return ERROR;

    stk->data = check;
    stk->capacity /= 4;
    return OK;
}

void StackAssertFunc(Stack * stk, int LINE, const char * FILE)
{
    if (stk->data)
    {
        stk->data = 0;
        stk->capacity = 0;
        free(stk->data);
    }
    fprintf(stderr, "StackAssert failed!\n[Line %d]\n[File %s]\n", LINE, FILE);
    abort();
}

void PrintStack(Stack * stk)
{
    printf("(stack capacity = %lu)\n", stk->capacity);
    printf("(stack size = %lu)\n", stk->size);

    printf("{");
    for (int i = stk->size - 1; i >= 0; i--)
    {
        if (i != 0) printf("%lg, ", stk->data[i]);
        else printf("%lg", stk->data[i]);
    }
    printf("}\n\n");
}
