#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "stack.h"
#include "hash.h"

/**********************************************************************************************

*   type BEGIN_CHECK and use only caps func (STACK_PUSH, STACK_POP, STACK_CTOR, STACK_DTOR etc.)
*   to turn on debug mode define DEBUG in stack.h
*   for correct STACK_DUMP work write your own PrintEl function (see example in stack.cpp)

_____________________________________________________________

*   before compiling please add a /bin folder in your project
*   (used in makefile for .o files and binary file)
_____________________________________________________________

*   this version has some errors like:
*   data nullptr check (fixing)
*   stk.size rewrite check (fixing)

***********************************************************************************************/

int main(void)
{
    BEGIN_CHECK
    Stack stk = {};
    char x = 120;
    if(STACK_CTOR(&stk, sizeof(int), 10) != SUCCESS) return ERROR;

    for (int i = 0; i < 100; i++)
        STACK_PUSH(&stk, &x);

    STACK_DUMP(&stk);
    return 0;
}
