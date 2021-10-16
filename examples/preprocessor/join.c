#include <stdlib.h>
#include <stdio.h>

#define SETUP_LIST(type, name, init_ln)\
	size_t name ## _ln;\
	type* name = malloc(sizeof(type) * (init_ln));\

#define SETUP_STATIC_LIST(type, name, ...)\
	type name[] = {__VA_ARGS__};\
	size_t name ## _ln = sizeof(name) / sizeof(name[0]);

int main()
{
	SETUP_STATIC_LIST(double, arrs, 0, 1, 2, 3, 4);

	/*double arr[5] = {1, 2, 3, 4, 5};

	SETUP_LIST(double, arr, 10);
	printf("%lf\n", arr[0]);*/
}
