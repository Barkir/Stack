#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "stack.h"

int StackCtor(Stack * stk, size_t stk_capacity ON_DEBUG(COMMA const char * NAME COMMA int LINE COMMA const char * FILE COMMA const char * FUNC))
{
#ifdef DEBUG
    stk->NAME = NAME;
    stk->LINE = LINE;
    stk->FUNC = FUNC;
    stk->FILE = FILE;
#endif

    stk->capacity = stk_capacity < 16 ? 16 : stk_capacity;
    stk->size = 0;
    stk->data = (StackEl_t*) calloc(stk->capacity, sizeof(StackEl_t));

    STACK_ASSERT(stk);
    return SUCCESS;
}

int StackDtor(Stack * stk)
{
    STACK_ASSERT(stk);
    stk->capacity = 0;
    stk->size = 0;

    free(stk->data);
    fprintf(stderr, "Stack Terminated!\n");

    STACK_ASSERT(stk);
    return SUCCESS;
}

int StackPush(Stack * stk, StackEl_t elem)
{
    STACK_ASSERT(stk);
    if (stk->size >= stk->capacity)
        if(StackExpand(stk) == ERROR) return ERROR;

    stk->data[stk->size] = elem;
    stk->size++;

    STACK_ASSERT(stk);
    return SUCCESS;
}

// top
// std::stack

int StackPop(Stack * stk)
{
    STACK_ASSERT(stk);
    StackEl_t elem = 0;

    if (stk->size < stk->capacity / 4)
        if (StackShrink(stk) == ERROR) return ERROR;

    elem = stk->data[stk->size];
    stk->data[stk->size] = 0;
    stk->size--;

    STACK_ASSERT(stk);
    return SUCCESS;
}

int StackExpand(Stack * stk)
{
    STACK_ASSERT(stk);
    StackEl_t * check = 0;
    if ((check = (StackEl_t*) realloc(stk->data, (stk->capacity * 2) * sizeof(*(stk->data)))) == NULL)
        return BADDATA;

    stk->data = check;
    stk->capacity *= 2;

    STACK_ASSERT(stk);
    return SUCCESS;
}

int StackShrink(Stack * stk)
{
    STACK_ASSERT(stk);
    StackEl_t * check = 0;
    if ((check = (StackEl_t*) realloc(stk->data, (stk->capacity / 4) * sizeof(*(stk->data)))) == NULL)
        return BADDATA;

    stk->data = check;
    stk->capacity /= 4;

    STACK_ASSERT(stk);
    return SUCCESS;
}

void StackAssertFunc(Stack * stk, int LINE, const char * FILE, const char * FUNC)
{
    int err = StackError(stk);
    if (err)
    {
        fprintf(stderr, "StackAssert failed! %s: %d (%s) (error code: %d)", FILE, LINE, FUNC, err);
        StackDump(stk, LINE, FILE, FUNC);
        abort();
    }
}

void StackDump(Stack * stk, int LINE, const char * CALL_FILE, const char * FUNC)
{
#ifdef DEBUG
    FILE * fp = fopen("stack.dmp", "wb");
    fprintf(fp, "Stack [%p]\n", &stk);
    fprintf(fp, "called from %s: %d -> (%s)\n", CALL_FILE, LINE, FUNC);
    fprintf(fp, "name \"%s\" born at %s: %d -> (%s)\n", stk->NAME, stk->FILE, stk->LINE, stk->FUNC);
    fprintf(fp, "\ncapacity = %lu\nsize = %lu\ndata[%p]\n", stk->capacity, stk->size, stk->data);
    if (!StackError(stk))
    {
        for (int i = stk->size; i >= 0; i--)
            if (isfinite(stk->data[i])) fprintf(fp, "*[%lu] = %lg\n", stk->size - i, stk->data[i]);
            else                        fprintf(fp, " [%lu] = %lg (pzn)\n", stk->size - i, stk->data[i]);
    }
    fclose(fp);
#endif
}

int StackError(Stack * stk)
{
    if (!stk)                                       return BADSTK;
    if (stk->size < 0 || stk->size > SIZE_MAX)      return BADSIZE;
    if (stk->capacity < 0)                          return BADCAP;
    if (!stk->data)                                 return BADDATA;
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
