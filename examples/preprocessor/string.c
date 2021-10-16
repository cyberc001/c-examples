#include <stdio.h>
#include <stdlib.h>

#define myassert(eval, action)\
if(!(eval))\
	if(#action[0] == '\0')\
		exit(1);\
	else\
		action;

int main()
{
	myassert(10 == 20, );
	printf("test\n");
}
