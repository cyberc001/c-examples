#include "perftest.h"
#include <stdio.h>

void heavy_loop()
{
	int mul = 1;

	for(int i = 0; i < 10e6; ++i){
		int m = mul * (i % 10) / (i % 2 + 1);
		mul += m;
	}
}
void heavy_loop_volatile()
{
	volatile int mul = 1;

	for(int i = 0; i < 10e6; ++i){
		int m = mul * (i % 10) / (i % 2 + 1);
		mul += m;
	}
}

int main()
{
	clock_t t1;

	PERFTEST_MEASURE(heavy_loop_volatile(), t1);
	printf("%lu\n", t1);
	PERFTEST_MEASURE(heavy_loop(), t1);
	printf("%lu\n", t1);
}
