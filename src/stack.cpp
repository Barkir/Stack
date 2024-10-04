#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#include "stack.h"
#include "hash.h"

int StackCtorFunc(Stack * stk, size_t stk_capacity ON_DEBUG(COMMA const char * NAME COMMA int LINE COMMA const char * FILE COMMA const char * FUNC))
{
#ifdef DEBUG
    stk->NAME = NAME;
    stk->LINE = LINE;
    stk->FUNC = FUNC;
    stk->FILE = FILE;
#endif

    if (stk_capacity == 0) return SUCCESS;

    stk->capacity = stk_capacity < 16 ? 16 : stk_capacity;
    stk->size = 0;
    stk->data = (StackEl_t*) calloc(stk->capacity ON_DEBUG(+ 2), sizeof(StackEl_t));

#ifdef DEBUG
    stk->data++;
    MurMur(stk->data, stk->capacity * sizeof(StackEl_t), SEED, &data_hash);
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
    CanaryInstall(stk);
#endif

    STACK_ASSERT(stk);
    return SUCCESS;
}

int StackDtorFunc(Stack * stk)
{
    STACK_ASSERT(stk);
    stk->capacity = 0;
    stk->size = 0;

    stk->data--;
    free(stk->data);
    printf("Stack Terminated!\n");
    return SUCCESS;
}

int StackPush(Stack * stk, StackEl_t elem)
{
    STACK_ASSERT(stk);
    if ((stk->size + 1) >= stk->capacity)
        if(StackExpand(stk) == ERROR) return ERROR;

    stk->size++;
    stk->data[stk->size - 1] = elem;
#ifdef DEBUG
    MurMur(stk->data, stk->capacity * sizeof(StackEl_t), SEED, &data_hash);
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
#endif

    STACK_ASSERT(stk);
    return SUCCESS;
}

// std::vector::shrink_to_fit
// TODO: two shrink pop, no shrink pop

int StackPop(Stack * stk)
{
    STACK_ASSERT(stk);
    if (stk->size <= stk->capacity / 4)
        if (StackShrink(stk) == ERROR) return ERROR;

    stk->data[stk->size - 1] = 0;
    stk->size--;

#ifdef DEBUG
    MurMur(stk->data, stk->capacity * sizeof(StackEl_t), SEED, &data_hash);
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
#endif

    STACK_ASSERT(stk);
    return SUCCESS;
}

StackEl_t StackTop(Stack * stk)
{
    STACK_ASSERT(stk);
    return stk->data[stk->size - 1];
}

int StackExpand(Stack * stk)
{
    STACK_ASSERT(stk);
    StackEl_t * check = 0;

    ON_DEBUG(stk->data--;)
    if ((check = (StackEl_t*) realloc(stk->data, (stk->capacity * 2 ON_DEBUG(+ 2)) * sizeof(*(stk->data)))) == NULL)
        return BADDATA;

    stk->data = check;
    stk->capacity *= 2;

#ifdef DEBUG
    stk->data++;
    memset(stk->data + stk->capacity / 2, pzn, stk->capacity / 2);
    MurMur(stk->data, stk->capacity * sizeof(StackEl_t), SEED, &data_hash);
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
    CanaryInstall(stk);
#endif

    STACK_ASSERT(stk);
    return SUCCESS;
}

int StackShrink(Stack * stk)
{
    STACK_ASSERT(stk);
    StackEl_t * check = 0;

    ON_DEBUG(stk->data--;)
    if ((check = (StackEl_t*) realloc(stk->data, (stk->capacity / 4 ON_DEBUG(+ 2)) * sizeof(*(stk->data)))) == NULL)
        return BADDATA;

    stk->data = check;
    stk->capacity /= 4;

#ifdef DEBUG
    stk->data++;
    MurMur(stk->data, stk->capacity * sizeof(StackEl_t), SEED, &data_hash);
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
    CanaryInstall(stk);
#endif

    STACK_ASSERT(stk);
    return SUCCESS;
}


// TODO: Func param
void StackAssertFunc(Stack * stk, int LINE, const char * FILE, const char * FUNC)
{
#ifdef DEBUG
    int err = StackError(stk);
    if (err)
    {
        fprintf(stderr, "StackAssert failed! %s: %d (%s) (error code: %d)", FILE, LINE, FUNC, err);
        StackDump(stk, LINE, FILE, FUNC);
        abort();
    }
#endif
}

void StackDump(Stack * stk, int LINE, const char * CALL_FILE, const char * FUNC)
{
#ifdef DEBUG
    FILE * fp = fopen("stack.dmp", "wb");
    fprintf(fp, "Stack [%p]\n", &stk);

    if (*LEFT_CANARY == 0xDEADBEEF)     fprintf(fp, "LeftCanary [%p] = %lg\n",           LEFT_CANARY,    *LEFT_CANARY);
    else                                fprintf(fp, "LeftCanary [%p] = %lg [DEAD⚰]\n",  LEFT_CANARY,    *LEFT_CANARY);
    if (*RIGHT_CANARY == 0xDEADBEEF)    fprintf(fp, "RightCanary [%p] = %lg\n",          RIGHT_CANARY,   *RIGHT_CANARY);
    else                                fprintf(fp, "RightCanary [%p] = %lg [DEAD⚰]\n", RIGHT_CANARY,   *RIGHT_CANARY);

    fprintf(fp, "called from %s: %d -> (%s)\n", CALL_FILE, LINE, FUNC);
    fprintf(fp, "name \"%s\" born at %s: %d -> (%s)\n", stk->NAME, stk->FILE, stk->LINE, stk->FUNC);
    fprintf(fp, "\ncapacity = %lu\nsize = %lu\ndata[%p]\n", stk->capacity, stk->size, stk->data);
    if (stk->data)
    {
        for (int i = stk->size - 1; i >= 0; i--)
            PrintEl(fp, stk->data[i], stk, i);
    }
    fclose(fp);
#endif
}

void PrintEl(FILE * fp, StackEl_t el, Stack * stk, int i)
{
    if (isfinite(el))           fprintf(fp, "*[%lu] = %lg\n", stk->size - i - 1, el);
    else                        fprintf(fp, " [%lu] = %lg (pzn)\n", stk->size - i - 1, el);
}

void PrintStack(Stack * stk)
{
    STACK_ASSERT(stk);
    printf("(stack capacity = %lu)\n", stk->capacity);
    printf("(stack size = %lu)\n", stk->size);

    printf("{");
    for (int i = stk->size - 1; i >= 0; i--)
    {
        if (i != 0) printf("%lg, ", stk->data[i]);
        else printf("%lg", stk->data[i]);
    }
    printf("}\n\n");
    STACK_ASSERT(stk);
}

int StackError(Stack * stk)
{
#ifdef DEBUG
    hash_t stack_hash_check = 0;
    hash_t data_hash_check = 0;

    MurMur(stk->data, stk->capacity * sizeof(StackEl_t), SEED, &data_hash_check);
    MurMur(stk, sizeof(stk), SEED, &stack_hash_check);

    if (!stk)                                                               return BADSTK;
    if (stk->size < 0 || stk->size > SIZE_MAX)                              return BADSIZE;
    if (stk->capacity < 0)                                                  return BADCAP;
    if (!stk->data)                                                         return BADDATA;
    if (data_hash_check != data_hash || stack_hash_check != stack_hash)     return WRONGHASH;
    if (LEFT_CANARY && RIGHT_CANARY)
        if (*LEFT_CANARY != 0xDEADBEEF || *RIGHT_CANARY != 0xDEADBEEF)      return DEADCANARY;
#endif
    return SUCCESS;

}

void CanaryInstall(Stack * stk)
{
#ifdef DEBUG

    stk->data--;
    *stk->data = 0xDEADBEEF;
    LEFT_CANARY = stk->data;

    stk->data++;

    *(stk->data + stk->capacity) = 0xDEADBEEF;
    RIGHT_CANARY = stk->data + stk->capacity;

    STACK_ASSERT(stk);
#endif
}
