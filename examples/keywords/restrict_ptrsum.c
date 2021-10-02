#include <stdio.h>

int ptrsum(int* a, int* b)
{
	*a += 15;
	*b += 17;
	return *a + *b;
}
int ptrsum_restrict(int* restrict a, int* restrict b)
{
	*a += 15;
	*b += 17;
	return *a + *b;
}


int main()
{
	int num;

	int* a = &num;
	int* restrict b = a;
}
