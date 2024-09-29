#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stack.h"

int main(void)
{

    Stack stk = {};
    if (STACK_CTOR(&stk, 1) != SUCCESS) return ERROR;
    PrintStack(&stk);

    STACK_DTOR(&stk);
    return 0;
}
