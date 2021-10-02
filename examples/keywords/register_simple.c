#include "perftest.h"

#include <stdio.h>
#include <stdlib.h>

void tight_for_loop()
{
	for(size_t i = 0; i < 1e7; ++i)
		;
}
void tight_for_loop_register()
{
	for(register size_t i = 0; i < 1e7; ++i)
		;
}


int main()
{
	clock_t t1;
	PERFTEST_MEASURE(tight_for_loop(), t1);
	printf("%lu\n", t1);
	PERFTEST_MEASURE(tight_for_loop_register(), t1);
	printf("%lu\n", t1);
}
