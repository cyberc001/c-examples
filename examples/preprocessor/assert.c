#include <stdio.h>
#include <stdlib.h>

#define MY_ASSERT(expr) if(!(expr)){\
	printf("assertion failed: \"%s\", %s:%d\n", # expr, __FILE__, __LINE__);\
	exit(0);\
}

int main()
{
	int x = 10;
	MY_ASSERT(x == 11);
}
