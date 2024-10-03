#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "stack.h"
#include "hash.h"

/**********************************************************************************************

*   type BEGIN_CHECK and use only caps func (STACK_PUSH, STACK_POP, STACK_CTOR, STACK_DTOR etc.)
*   to turn on debug mode define DEBUG in stack.h

***********************************************************************************************/

int main(void)
{
    BEGIN_CHECK
    Stack stk = {};
    STACK_CTOR(&stk, 10);
    for (int i = 0; i < 63; i++)
        STACK_PUSH(&stk, 10);
    PrintStack(&stk);
        for (int i = 0; i < 48; i++)
        STACK_POP(&stk);
    PrintStack(&stk);
    return 0;
}
