#ifndef STACK_H
#define STACK_H

#define DEBUG

#ifdef DEBUG
#define ON_DEBUG(code) code
#define STACK_ASSERT(stk) StackAssertFunc((stk), (__LINE__), (__FILE__), (__func__))
#else
#define ON_DEBUG(code)
#define STACK_ASSERT(stk)
#endif

typedef double StackEl_t;

#define COMMA ,
#define SIZE_MAX 100000

#define STACK_CTOR(stk, cap) StackCtor((stk), (cap) ON_DEBUG(COMMA (#stk) COMMA (__LINE__) COMMA (__FILE__) COMMA (__func__)))
#define STACK_DTOR(stk) StackDtor(stk)
#define STACK_DUMP(stk) StackDump(stk, __LINE__, __FILE__, __func__)

#define BEGIN_CHECK double err = 0;
#define STACK_PUSH(stk, num) if (!err) err = StackPush(stk, num); else STACK_ASSERT(stk)
#define STACK_POP(stk) if (!err) err = StackPop(stk); else STACK_ASSERT(stk)


enum err_val
{
    SUCCESS = 0,
    BADSIZE = 1,
    BADCAP = 2,
    BADSTK = 3,
    BADDATA = 4,
    ERROR = 5
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

int StackCtor(Stack * stk, size_t stk_capacity \
                ON_DEBUG(COMMA const char * NAME COMMA int LINE COMMA const char * FILE COMMA const char * FUNC));
int StackDtor(Stack * stk);

int StackPush(Stack * stk, StackEl_t elem);
int StackPop(Stack * stk);

int StackExpand(Stack * stk);
int StackShrink(Stack * stk);

void PrintStack(Stack * stk);

int StackError(Stack * stk);
void StackAssertFunc(Stack * stk, int LINE, const char * CALL_FILE, const char * FUNC);
void StackDump(Stack * stk, int LINE, const char * FILE, const char * FUNC);

#endif
