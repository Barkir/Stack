#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main(void)
{
    Stack stk = {};
    if (Stack_Ctor(&stk, 1) == ERROR) return ERROR;
    PrintStack(&stk);

    Push(&stk, 10);
    Push(&stk, 20);

    PrintStack(&stk);

    Pop(&stk);
    PrintStack(&stk);
    Push(&stk, 20);
    Push(&stk, 30);
    Push(&stk, 40);
    PrintStack(&stk);
    Push(&stk, 50);
    PrintStack(&stk);
    Pop(&stk);
    Pop(&stk);
    PrintStack(&stk);
    Stack_Dtor(&stk);

    return 0;
}
