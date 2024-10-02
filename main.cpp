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
    STACK_PUSH(&stk, 10);
    STACK_PUSH(&stk, 10);
    return 0;
}
