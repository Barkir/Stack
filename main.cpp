#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stack.h"

/**********************************************************************************************

*   type BEGIN_CHECK and use only caps func (STACK_PUSH, STACK_POP, STACK_CTOR, STACK_DTOR etc.)
*   to turn on debug mode define DEBUG in stack.h

***********************************************************************************************/

int main(void)
{
    BEGIN_CHECK

    Stack stk = {};
    if (STACK_CTOR(&stk, 16) != SUCCESS) return ERROR;
    PrintStack(&stk);
    for (int i = 0; i < 10; i++)
    {
        STACK_PUSH(&stk, i);
        printf("top = %lg\n", STACK_TOP(&stk));
    }
    PrintStack(&stk);

    STACK_DTOR(&stk);
    return 0;
}
