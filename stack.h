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
typedef double Cannary_t;

#define COMMA ,
#define SIZE_MAX 100000

#define STACK_CTOR(stk, cap) StackCtorFunc((stk), (cap) ON_DEBUG(COMMA (#stk) COMMA (__LINE__) COMMA (__FILE__) COMMA (__func__)))
#define STACK_DTOR(stk) StackDtorFunc(stk)
#define STACK_DUMP(stk) StackDump(stk, __LINE__, __FILE__, __func__)

#define BEGIN_CHECK int err = 0;
#define STACK_PUSH(stk, num) if (!err) err = StackPush(stk, num); else return -1
#define STACK_POP(stk) if (!err) err = StackPop(stk); else return -1
#define STACK_TOP(stk) StackTop(stk)

static Cannary_t * LEFT_CANARY = 0;
static Cannary_t * RIGHT_CANARY = 0;
const static StackEl_t pzn = -666;

// TODO: void*
// TODO: error description
enum err_val
{
    SUCCESS = 0,
    BADSIZE = 1,
    BADCAP = 2,
    BADSTK = 3,
    BADDATA = 4,
    DEADCANARY = 5,
    WRONGHASH = 6,
    ERROR = 7
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

struct Torture
{
    char * LeftExec;
    Stack stk;
    char * RightExec;
};

int StackCtorFunc(Stack * stk, size_t stk_capacity \
                ON_DEBUG(COMMA const char * NAME COMMA int LINE COMMA const char * FILE COMMA const char * FUNC));
int StackDtorFunc(Stack * stk);

int StackPush(Stack * stk, StackEl_t elem);
int StackPop(Stack * stk);
StackEl_t StackTop(Stack * stk);

int StackExpand(Stack * stk);
int StackShrink(Stack * stk);

void PrintStack(Stack * stk);
void PrintEl(FILE * fp, StackEl_t el, Stack * stk, int i);

int StackError(Stack * stk);
void StackAssertFunc(Stack * stk, int LINE, const char * CALL_FILE, const char * FUNC);
void StackDump(Stack * stk, int LINE, const char * FILE, const char * FUNC);

void CanaryInstall(Stack * stk);

#endif
