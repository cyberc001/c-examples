#include <stdio.h>

enum clr{
	RED, BLUE, GREEN, YELLOW, WHITE, BLACK
};

#define PRINT_CLR_CODE(clr) printf(#clr " = %d\n", clr);

int main()
{
	PRINT_CLR_CODE(GREEN);

	printf("A simple message\n"
	       "I am demonstrating.\n");
}
