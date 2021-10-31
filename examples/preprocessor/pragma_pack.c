#include <stdlib.h>
#include <stdio.h>
#include <stdalign.h>

# pragma pack(2)
struct s{
	int i;		// 4
	char j;		// 1
	double k;	// 8
};

int main()
{
	struct s s1, s2;
	printf("%lu\n", sizeof(s1));
}
