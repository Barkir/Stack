#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#include "stack.h"
#include "hash.h"

<<<<<<< HEAD
int StackCtorFunc(Stack * stk, size_t el_size, size_t stk_capacity ON_DEBUG(COMMA const char * NAME COMMA int LINE COMMA const char * FILE COMMA const char * FUNC))
=======
int StackCtorFunc(Stack * stk, size_t stk_capacity ON_DEBUG(COMMA const char * NAME COMMA int LINE COMMA const char * FILE COMMA const char * FUNC))
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5
{
#ifdef DEBUG
    stk->NAME = NAME;
    stk->LINE = LINE;
    stk->FUNC = FUNC;
    stk->FILE = FILE;
#endif

    if (stk_capacity == 0) return SUCCESS;
<<<<<<< HEAD
    if (stk_capacity > MAX_SIZE || stk_capacity < 0) return BADCAP;
    stk->capacity = stk_capacity < 16 ? 16 : stk_capacity;
    stk->size = 0;
    stk->el_size = el_size;
    stk->data = malloc(stk->capacity * stk->el_size ON_DEBUG(+ CannaryShift(stk->capacity * stk->el_size)));
    memset(stk->data, 0, stk->capacity * stk->el_size ON_DEBUG(+ CannaryShift(stk->capacity * stk->el_size)));

#ifdef DEBUG
    stk->data = (void*)((size_t) stk->data + CannarySize);
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
    MurMur(stk->data, stk->capacity * stk->el_size, SEED, &data_hash);
    CannaryInstall(stk);
=======

    stk->capacity = stk_capacity < 16 ? 16 : stk_capacity;
    stk->size = 0;
    stk->data = (StackEl_t*) calloc(stk->capacity ON_DEBUG(+ 2), sizeof(StackEl_t));

#ifdef DEBUG
    stk->data++;
    MurMur(stk->data, stk->capacity * sizeof(StackEl_t), SEED, &data_hash);
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
    CanaryInstall(stk);
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5
#endif

    STACK_ASSERT(stk);
    return SUCCESS;
}

int StackDtorFunc(Stack * stk)
{
    STACK_ASSERT(stk);
    stk->capacity = 0;
    stk->size = 0;
<<<<<<< HEAD
    stk->el_size = 0;

    stk->data = (void*)((size_t) stk->data - CannarySize);
    free(stk->data);
    fprintf(stderr, "Stack Terminated!\n");
    return SUCCESS;
}

int StackPush(Stack * stk, void * elem)
=======

    stk->data--;
    free(stk->data);
    printf("Stack Terminated!\n");
    return SUCCESS;
}

int StackPush(Stack * stk, StackEl_t elem)
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5
{
    STACK_ASSERT(stk);
    if ((stk->size + 1) >= stk->capacity)
        if(StackExpand(stk) == ERROR) return ERROR;

    stk->size++;
<<<<<<< HEAD
    memcpy((void*)(((size_t)stk->data) + (stk->size - 1) * stk->el_size), elem, stk->el_size);

#ifdef DEBUG
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
    MurMur(stk->data, stk->capacity * stk->el_size, SEED, &data_hash);
=======
    stk->data[stk->size - 1] = elem;
#ifdef DEBUG
    MurMur(stk->data, stk->capacity * sizeof(StackEl_t), SEED, &data_hash);
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5
#endif

    STACK_ASSERT(stk);
    return SUCCESS;
}

// std::vector::shrink_to_fit
<<<<<<< HEAD
// TODO: to shrink pop, no shrink pop
=======
// TODO: two shrink pop, no shrink pop
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5

int StackPop(Stack * stk)
{
    STACK_ASSERT(stk);
    if (stk->size <= stk->capacity / 4)
        if (StackShrink(stk) == ERROR) return ERROR;

<<<<<<< HEAD
    memset((void*)((size_t)stk->data + (stk->size - 1) * stk->el_size), 0, stk->el_size);
    stk->size--;

#ifdef DEBUG
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
    MurMur(stk->data, stk->capacity * stk->el_size, SEED, &data_hash);
=======
    stk->data[stk->size - 1] = 0;
    stk->size--;

#ifdef DEBUG
    MurMur(stk->data, stk->capacity * sizeof(StackEl_t), SEED, &data_hash);
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5
#endif

    STACK_ASSERT(stk);
    return SUCCESS;
}

<<<<<<< HEAD
void * StackTop(Stack * stk)
{
    STACK_ASSERT(stk);
    return (void*)((size_t)stk->data + (stk->size - 1) * stk->el_size);
=======
StackEl_t StackTop(Stack * stk)
{
    STACK_ASSERT(stk);
    return stk->data[stk->size - 1];
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5
}

int StackExpand(Stack * stk)
{
    STACK_ASSERT(stk);
<<<<<<< HEAD
    void * check = 0;

    ON_DEBUG(stk->data = (void*)((size_t) stk->data - CannarySize);)
    if ((check = realloc(stk->data, (stk->capacity * 2 * stk->el_size ON_DEBUG(+ CannaryShift(stk->capacity * 2 * stk->el_size))))) == NULL)
=======
    StackEl_t * check = 0;

    ON_DEBUG(stk->data--;)
    if ((check = (StackEl_t*) realloc(stk->data, (stk->capacity * 2 ON_DEBUG(+ 2)) * sizeof(*(stk->data)))) == NULL)
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5
        return BADDATA;

    stk->data = check;
    stk->capacity *= 2;

#ifdef DEBUG
<<<<<<< HEAD
    stk->data = (void*)((size_t) stk->data + CannarySize);
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
    MurMur(stk->data, stk->capacity * stk->el_size, SEED, &data_hash);
    CannaryInstall(stk);
=======
    stk->data++;
    memset(stk->data + stk->capacity / 2, pzn, stk->capacity / 2);
    MurMur(stk->data, stk->capacity * sizeof(StackEl_t), SEED, &data_hash);
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
    CanaryInstall(stk);
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5
#endif

    STACK_ASSERT(stk);
    return SUCCESS;
}

int StackShrink(Stack * stk)
{
    STACK_ASSERT(stk);
<<<<<<< HEAD
    void * check = 0;

    ON_DEBUG(stk->data = (void*)((size_t) stk->data - CannarySize);)
    if ((check = realloc(stk->data, ((stk->capacity / 4) * stk->el_size ON_DEBUG(+ CannaryShift((stk->capacity / 4) * stk->el_size))))) == NULL)
=======
    StackEl_t * check = 0;

    ON_DEBUG(stk->data--;)
    if ((check = (StackEl_t*) realloc(stk->data, (stk->capacity / 4 ON_DEBUG(+ 2)) * sizeof(*(stk->data)))) == NULL)
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5
        return BADDATA;

    stk->data = check;
    stk->capacity /= 4;

#ifdef DEBUG
<<<<<<< HEAD
    stk->data = (void*)((size_t) stk->data + CannarySize);
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
    MurMur(stk->data, stk->capacity * stk->el_size, SEED, &data_hash);
    CannaryInstall(stk);
=======
    stk->data++;
    MurMur(stk->data, stk->capacity * sizeof(StackEl_t), SEED, &data_hash);
    MurMur(stk, sizeof(stk), SEED, &stack_hash);
    CanaryInstall(stk);
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5
#endif

    STACK_ASSERT(stk);
    return SUCCESS;
}


// TODO: Func param
void StackAssertFunc(Stack * stk, int LINE, const char * FILE, const char * FUNC)
{
#ifdef DEBUG
<<<<<<< HEAD
    Error = StackError(stk);
    if (Error)
    {
        fprintf(stderr, "StackAssert failed! %s: %d (%s) (error code: %d)", FILE, LINE, FUNC, Error);
=======
    int err = StackError(stk);
    if (err)
    {
        fprintf(stderr, "StackAssert failed! %s: %d (%s) (error code: %d)", FILE, LINE, FUNC, err);
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5
        StackDump(stk, LINE, FILE, FUNC);
        abort();
    }
#endif
}

<<<<<<< HEAD
=======
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

>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5
int StackError(Stack * stk)
{
#ifdef DEBUG
    hash_t stack_hash_check = 0;
    hash_t data_hash_check = 0;

<<<<<<< HEAD
    MurMur(stk, sizeof(stk), SEED, &stack_hash_check);
    // fprintf(stderr, "stack_hash = %d\n", stack_hash_check);
    MurMur(stk->data, stk->capacity * stk->el_size, SEED, &data_hash_check);
    // fprintf(stderr, "data_hash = %d\n", data_hash_check);

    if (stk == NULL)                                                        return BADSTK;
    if (stk->size < 0 || stk->size > MAX_SIZE)                              return BADSIZE;
    if (stk->capacity < 0 || stk->capacity > MAX_SIZE)                      return BADCAP;
    if (stk->data == NULL)                                                  return BADDATA;
    if (stack_hash_check != stack_hash)                                     return WRONGSTACKHASH;
    if (data_hash_check != data_hash)                                       return WRONGDATAHASH;
    if (LEFT_CANNARY && RIGHT_CANNARY)
        if (*LEFT_CANNARY != 0xDEADBEEF || *RIGHT_CANNARY != 0xDEADBEEF)    return DEADCANARY;
=======
    MurMur(stk->data, stk->capacity * sizeof(StackEl_t), SEED, &data_hash_check);
    MurMur(stk, sizeof(stk), SEED, &stack_hash_check);

    if (!stk)                                                               return BADSTK;
    if (stk->size < 0 || stk->size > SIZE_MAX)                              return BADSIZE;
    if (stk->capacity < 0)                                                  return BADCAP;
    if (!stk->data)                                                         return BADDATA;
    if (data_hash_check != data_hash || stack_hash_check != stack_hash)     return WRONGHASH;
    if (LEFT_CANARY && RIGHT_CANARY)
        if (*LEFT_CANARY != 0xDEADBEEF || *RIGHT_CANARY != 0xDEADBEEF)      return DEADCANARY;
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5
#endif
    return SUCCESS;

}

<<<<<<< HEAD
void StackDump(Stack * stk, int LINE, const char * CALL_FILE, const char * FUNC)
{
#ifdef DEBUG
    FILE * fp = fopen("stack.dmp", "wb");

    fprintf(fp, "Stack [%p]\n", stk);
    if (Error == WRONGSTACKHASH)         fprintf(fp, "MurMurStack: (imposter is here): %d 𐐘💥╾━╤デ╦︻ඞා\n", stack_hash);
    else                                 fprintf(fp, "MurMurStack: %d\n", stack_hash);


    if (*LEFT_CANNARY == 0xDEADBEEF)     fprintf(fp, "LeftCannary [%p] = %ld\n",           LEFT_CANNARY,    *LEFT_CANNARY);
    else                                 fprintf(fp, "LeftCannary [%p] = %ld [DEAD⚰]\n",  LEFT_CANNARY,    *LEFT_CANNARY);
    if (*RIGHT_CANNARY == 0xDEADBEEF)    fprintf(fp, "RightCannary [%p] = %ld\n",          RIGHT_CANNARY,   *RIGHT_CANNARY);
    else                                 fprintf(fp, "RightCannary [%p] = %ld [DEAD⚰]\n", RIGHT_CANNARY,   *RIGHT_CANNARY);

    fprintf(fp, "called from %s: %d -> (%s)\n", CALL_FILE, LINE, FUNC);
    fprintf(fp, "name \"%s\" born at %s: %d -> (%s)\n", stk->NAME, stk->FILE, stk->LINE, stk->FUNC);
    fprintf(fp, "\ncapacity = %lu\nsize = %lu\ndata[%p]\n", stk->capacity, stk->size, stk->data);
    if (Error == WRONGDATAHASH)          fprintf(fp, "MurMurData: (imposter is here): %d 𐐘💥╾━╤デ╦︻ඞා\n", data_hash);
    else                                 fprintf(fp, "MurMurStack: %d\n", data_hash);
    if (stk->data)
    {
        for (int i = stk->size - 1; i >= 0; i--)
            PrintEl(fp, (void*)((size_t)stk->data + i * stk->el_size), stk, i);
    }
    fclose(fp);
#endif
}

void PrintEl(FILE * fp, void * el, Stack * stk, int i)
{
    int toPrint = *(int*) el;
    if (toPrint != 666)         fprintf(fp, "*[%lu] = %c\n", stk->size - i - 1, toPrint);
    else                        fprintf(fp, " [%lu] = %c (pzn)\n", stk->size - i - 1, toPrint);
}

void CannaryInstall(Stack * stk)
{
#ifdef DEBUG
    Cannary_t CanVal = 0xDEADBEEF;
    stk->data = (void*)((size_t) stk->data - CannarySize);
    memcpy(stk->data, &CanVal, CannarySize);
    LEFT_CANNARY = (uint64_t*)(stk->data);
    stk->data = (void*)((size_t) stk->data + CannarySize);

    size_t adr = (size_t)stk->data + stk->capacity * stk->el_size;
    memcpy((void*)(adr + CannaryShift(adr) - 2 * CannarySize), &CanVal, CannarySize);
    RIGHT_CANNARY = (uint64_t*)(adr + CannaryShift(adr) - 2 * CannarySize);

=======
void CanaryInstall(Stack * stk)
{
#ifdef DEBUG

    stk->data--;
    *stk->data = 0xDEADBEEF;
    LEFT_CANARY = stk->data;

    stk->data++;

    *(stk->data + stk->capacity) = 0xDEADBEEF;
    RIGHT_CANARY = stk->data + stk->capacity;
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5

    STACK_ASSERT(stk);
#endif
}
<<<<<<< HEAD

size_t CannaryShift(size_t size)
{
#ifdef DEBUG
    if (size % CannarySize == 0) return 2 * CannarySize;
    return 2 * (CannarySize) + CannarySize - (size % CannarySize);
#endif
}
=======
>>>>>>> cefb24008ea6da09b564e39488f229cbbbd31ae5
