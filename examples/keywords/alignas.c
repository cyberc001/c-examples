#include <stdalign.h>
#include <stdio.h>

struct ostream
{
	int fd;
	alignas(8) unsigned char buf[16];
};


int main()
{
	printf("align of ostream: %lu\n", alignof(struct ostream));
	printf("size of ofstream: %lu\n", sizeof(struct ostream));
}
