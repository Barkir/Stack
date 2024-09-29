#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stack.h"

int main(void)
{
    BEGIN_CHECK

    Stack stk = {};
    if (STACK_CTOR(&stk, 1) != SUCCESS) return ERROR;
    PrintStack(&stk);
    StackPush(&stk, 1);
    STACK_DTOR(&stk);
    return 0;
}
