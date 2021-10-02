#include "perftest.h"

#include <stdio.h>
#include <stdlib.h>

int next_rand(int n)
{
	n *= 6498329132;
}
static inline int next_rand_inline(int n)
{
	n *= 6498329132;
}

int main()
{
	clock_t t1;
	int n = 15;
	PERFTEST_MEASURE_LOOP(next_rand(n), 10e6, t1);
	printf("%lu\n", t1);
	PERFTEST_MEASURE_LOOP(next_rand_inline(n), 10e6, t1);
	printf("%lu\n", t1);
}
