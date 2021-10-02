#include "perftest.h"

#include <stdlib.h>
#include <stdio.h>

void my_memmove(void* dest, const void* src, size_t n)
{
	for(void* dest_end = dest + n; dest != dest_end; ++dest, ++src)
		*((char*)dest) = *((char*)src);
}
void my_memmove_restrict(void* restrict dest, const void* restrict src, size_t n)
{
	for(void* dest_end = dest + n; dest != dest_end; ++dest, ++src)
		*((char*)dest) = *((char*)src);
}

int main()
{
	clock_t t1;
	{
		int arr1[1000]; for(size_t i = 0; i < 1000; ++i) arr1[i] = i;
		int arr2[1000];

		PERFTEST_MEASURE(my_memmove_restrict(arr1, arr1 + 2, 5), t1);
		printf("%lu\n", t1);

		for(size_t i = 0; i < 10; ++i)
			printf("%d ", arr1[i]);
		puts("");
	}
	{
		int arr1[1000]; for(size_t i = 0; i < 1000; ++i) arr1[i] = i;
		int arr2[1000];

		PERFTEST_MEASURE(my_memmove(arr1, arr1 + 2, 5), t1);
		printf("%lu\n", t1);

		for(size_t i = 0; i < 10; ++i)
			printf("%d ", arr1[i]);
		puts("");
	}
}
