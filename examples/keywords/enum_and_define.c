#include <stdio.h>

#define DEF_KINDERGARTEN 	(short)1
#define DEF_PRESCHOOL		(short)3
#define DEF_MIDDLESCHOOL	(short)4
#define DEF_HIGHSCHOOL 		(short)5
#define DEF_COLLEGE		(short)10
#define DEF_UNIVERSITY		(short)11

enum institution
{
	ENUM_KINDERGARTEN = (short)1,
	ENUM_PRESCHOOL = (short)3,
	ENUM_MIDDLESCHOOL,
	ENUM_HIGHSCHOOL,
	ENUM_COLLEGE = (short)10,
	ENUM_UNIVERSITY
};

int main()
{
	int *a = &ENUM_KINDERGARTEN;
	printf("Preschool enum: %d|%d\n", DEF_PRESCHOOL, ENUM_PRESCHOOL);
	printf("Sizeof: %lu|%lu\n", sizeof(DEF_PRESCHOOL), sizeof(ENUM_PRESCHOOL));
}
