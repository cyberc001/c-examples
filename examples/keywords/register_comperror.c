#include <stdio.h>

/// compile in tcc

void print_register()
{
	register int arr[2];
	arr[0] = 15;
	arr[1] = 35;
	printf("%d %d\n", arr[0], arr[1]);
}

int main()
{
	register int a;
	int* a_ptr = &a;
}
