#ifndef STACK_H
#define STACK_H

typedef double StackEl_t;

#define StackAssert(stk) StackAssertFunc(stk, __LINE__, __FILE__)

enum err_val
{
    OK,
    ERROR
};

struct Stack
{
    StackEl_t * data;
    size_t size, capacity;
};

int Stack_Ctor(Stack * stk, size_t stk_capacity);
int Stack_Dtor(Stack * stk);
StackEl_t StackPush(Stack * stk, StackEl_t elem);
int StackExpand(Stack * stk);
int StackShrink(Stack * stk);
StackEl_t StackPop(Stack * stk);
void PrintStack(Stack * stk);
void StackAssertFunc(Stack * stk, int LINE, const char * FILE);

#endif
