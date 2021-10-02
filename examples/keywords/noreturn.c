#include <stdlib.h>
#include <stdio.h>
#include <stdnoreturn.h>

void startup_report(const char* module_name, const char* message)
{
	fprintf(stderr, "[STARTUP:%-10s] %s\n", module_name, message);
}

noreturn void crash_report(const char* module_name, const char* message)
{
	fprintf(stderr, "[FATAL:%-10s] %s\n", module_name, message);
	exit(-1);
}

int main()
{
	startup_report("main", "Program start");
	crash_report("main", "Crash test");
	printf("Recovery after crash\n");
}
