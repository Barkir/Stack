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

    Torture Dead = {};
    if (STACK_CTOR(&Dead.stk, 10) != SUCCESS) return ERROR;
    for (int i = 0; i < 5; i++)
        STACK_PUSH(&Dead.stk, i);

    STACK_PUSH(&Dead.stk, NAN);
    Dead.LeftExec = (char*) Dead.stk.data - 1;
    PrintStack(&Dead.stk);
    *Dead.LeftExec = 1;
    STACK_PUSH(&Dead.stk, 10);

    return 0;
}
