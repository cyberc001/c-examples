#include <stdio.h>

struct {
	int SCHOLAR, STUDENT, WORKER, TEACHER, MEDICAL_WORKER, MILITARY_SERVICE;
} occupation_type = {1, 2, 5, 10, 11, 20};

int main()
{
	printf("Studying enums: %d %d\n", occupation_type.SCHOLAR, occupation_type.STUDENT);
	printf("Funded enums: %d %d %d\n", occupation_type.TEACHER, occupation_type.MEDICAL_WORKER,
					  occupation_type.MILITARY_SERVICE);
}
