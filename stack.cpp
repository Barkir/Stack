#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "stack.h"

int DoStackCtor(Stack * stk, size_t stk_capacity, const char * NAME, int LINE, const char * FILE, const char * FUNC)
{
    ON_DEBUG(stk->NAME = NAME;)
    ON_DEBUG(stk->LINE = LINE;)
    ON_DEBUG(stk->FUNC = FUNC;)
    ON_DEBUG(stk->FILE = FILE;)

    stk->capacity = stk_capacity < 16 ? 16 : stk_capacity;
    stk->size = 0;
    stk->data = (StackEl_t*) calloc(stk->capacity, sizeof(StackEl_t));

    assert(stk->data);
    return SUCCESS;
}

int DoStackDtor(Stack * stk)
{
    stk->capacity = 0;
    stk->size = 0;

    assert(stk->data);
    free(stk->data);
    fprintf(stderr, "Stack Terminated!\n");
    return SUCCESS;
}

int DoStackPush(Stack * stk, StackEl_t elem)
{
    if (stk->size >= stk->capacity)
        if(StackExpand(stk) == ERROR) return ERROR;

    stk->data[stk->size] = elem;
    stk->size++;
    return SUCCESS;
}

// top
// std::stack

int DoStackPop(Stack * stk)
{
    StackEl_t elem = 0;

    if (stk->size < stk->capacity / 4)
        if (StackShrink(stk) == ERROR) return ERROR;

    elem = stk->data[stk->size];
    stk->data[stk->size] = 0;
    stk->size--;
    return SUCCESS;
}

int StackExpand(Stack * stk)
{
    StackEl_t * check = 0;
    if ((check = (StackEl_t*) realloc(stk->data, (stk->capacity * 2) * sizeof(*(stk->data)))) == NULL)
        return BADDATA;

    stk->data = check;
    stk->capacity *= 2;
    return SUCCESS;
}

int StackShrink(Stack * stk)
{
    StackEl_t * check = 0;
    if ((check = (StackEl_t*) realloc(stk->data, (stk->capacity / 4) * sizeof(*(stk->data)))) == NULL)
        return BADDATA;

    stk->data = check;
    stk->capacity /= 4;
    return SUCCESS;
}

void StackAssertFunc(Stack * stk, int LINE, const char * FILE, const char * FUNC)
{
    int err = StackError(stk);
    if (!err)
    {
        fprintf(stderr, "StackAssert failed! %s: %d (%s) (error code: %d)", FILE, LINE, FUNC, err);
        abort();
    }
}

void StackDump(Stack * stk)
{
    FILE * fp = fopen("stack.dmp", "wb");

}

int StackError(Stack * stk)
{
    if (!stk)               return BADSTK;
    if (stk->size < 0)      return BADSIZE;
    if (stk->capacity < 0)  return BADCAP;
    if (!stk->data)         return BADDATA;
    return SUCCESS;
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
