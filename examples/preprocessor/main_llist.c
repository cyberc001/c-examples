#include <stdio.h>
#include <time.h>

#include "linked_list.h"
DEF_LLIST(i, int)

void it_listi(int i)
{
	printf("%d ", i);
}

int main()
{
	llist_i l1;
	llist_i_new(&l1);

	srand(time(NULL));
	for(size_t i = 0; i < 10; ++i)
		llist_i_insert_end(&l1, rand() % 101);
	llist_i_iterate(&l1, it_listi); printf("\n");

	llist_i_delete(&l1);
}
