#ifndef STACK_H
#define STACK_H

//#define DEBUG

#ifdef DEBUG
#define ON_DEBUG(code) code
#else
#define ON_DEBUG(code)
#endif

typedef double StackEl_t;

#define COMMA ,

#define STACK_ASSERT(stk) StackAssertFunc((stk), (__LINE__), (__FILE__), (__func__))
#define STACK_CTOR(stk, cap) DoStackCtor((stk), (cap), (#stk), (__LINE__), (__FILE__), (__func__))
#define STACK_DTOR(stk) DoStackDtor(stk)

#define BEGIN_CHECK double err = 0;
#define STACK_PUSH(stk, num) if (!err) err = DoStackPush(stk, num); else StackAssert(stk)
#define STACK_POP(stk) if (!err) err = DoStackPop(stk); else StackAssert(stk)


enum err_val
{
    SUCCESS,
    BADSIZE,
    BADCAP,
    BADSTK,
    BADDATA,
    ERROR
};

struct Stack
{
    ON_DEBUG(int LINE;)
    ON_DEBUG(const char * FUNC;)
    ON_DEBUG(const char * FILE;)
    ON_DEBUG(const char * NAME;)

    StackEl_t * data;
    size_t size, capacity;
};

int DoStackPush(Stack * stk, StackEl_t elem);
int DoStackPop(Stack * stk);
int DoStackCtor(Stack * stk, size_t stk_capacity, const char * NAME, int LINE, const char * FILE, const char * FUNC);
int DoStackDtor(Stack * stk);
int StackError(Stack * stk);
int StackExpand(Stack * stk);
int StackShrink(Stack * stk);
void PrintStack(Stack * stk);
void StackAssertFunc(Stack * stk, int LINE, const char * FILE, const char * FUNC);

#endif
