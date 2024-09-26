#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stack.h"

#define BEGIN_CHECK double err = 0;
#define CHECKED_Push(stk, num) if (!isnan(err)) err = Push(stk, num); else return -1
#define CHECKED_Pop(stk) if (!isnan(err)) err = Pop(stk); else return -1

int main(void)
{
    BEGIN_CHECK

    Stack stk = {};
    if (Stack_Ctor(&stk, 1) == ERROR) return ERROR;
    PrintStack(&stk);

    CHECKED_Push(&stk, 10);
    CHECKED_Push(&stk, 20);

    PrintStack(&stk);

    CHECKED_Pop(&stk);
    PrintStack(&stk);
    CHECKED_Push(&stk, 40);
    CHECKED_Push(&stk, 30);
    CHECKED_Push(&stk, 50);
    PrintStack(&stk);
    CHECKED_Push(&stk, 50);
    PrintStack(&stk);
    CHECKED_Pop(&stk);
    CHECKED_Pop(&stk);
    PrintStack(&stk);
    Stack_Dtor(&stk);

    return 0;
}
