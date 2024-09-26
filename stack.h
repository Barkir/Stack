#ifndef STACK_H
#define STACK_H

typedef double StackEl_t;

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
StackEl_t Push(Stack * stk, StackEl_t elem);
int StackExpand(Stack * stk);
int StackShrink(Stack * stk);
StackEl_t Pop(Stack * stk);
void PrintStack(Stack * stk);

#endif
