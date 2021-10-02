#include "perftest.h"

#include <stdio.h>
#include <stdlib.h>

void tight_for_loop()
{
	int a = 1;
	for(size_t i = 0; i < 1e9; ++i)
		a *= 7;
}
void tight_for_loop_register()
{
	int a = 1;
	for(register size_t i = 0; i < 1e9; ++i)
		a *= 7;
}
void tight_for_loop_register2()
{
	register int a = 1;
	for(size_t i = 0; i < 1e9; ++i)
		a *= 7;
}


int main()
{
	clock_t t1;
	PERFTEST_MEASURE(tight_for_loop(), t1);
	printf("%lu\n", t1);
	PERFTEST_MEASURE(tight_for_loop_register(), t1);
	printf("%lu\n", t1);
	PERFTEST_MEASURE(tight_for_loop_register2(), t1);
	printf("%lu\n", t1);
}
