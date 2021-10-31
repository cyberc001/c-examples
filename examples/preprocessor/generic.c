#include <stdio.h>

void print_int(int o)
{
	printf("int: %d\n", o);
}
void print_double(double o)
{
	printf("%lf\n", o);
}

#define print(o) _Generic(o,\
			  int : print_int((int)o),\
			  double : print_double((double)o),\
			  default: print_int((int)o))

int main()
{
	unsigned long long x = 10;
	print(x);
}
