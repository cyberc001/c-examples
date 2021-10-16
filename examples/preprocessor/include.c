#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define arr_min(_arr, _arr_ln, _out)\
{\
	_out = (_arr)[0];\
	for(size_t i = 1; i < (_arr_ln); ++i)\
		if((_arr)[i] < (_out))\
			_out = (_arr)[i];\
}


int main()
{
	srand(time(NULL));

	int* arr = malloc(10 * sizeof(int));
	for(size_t i = 0; i < 10; ++i)
		arr[i] = rand() % 100 - 50;
	for(size_t i = 0; i < 10; ++i)
		printf("%d ", arr[i]);
	puts("");

	int** arr_ptr = &arr;

	int arr_m;
	arr_min(*arr_ptr, 10, arr_m);
	printf("%d\n", arr_m);
}
