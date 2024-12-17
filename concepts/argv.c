#include <stdio.h>

int main(int argc, char **argv)
{
	(void) argc;

	while (*argv != NULL) {  // Loop until the NULL pointer is reached
		printf("%s\n", *argv);
		argv++;  // Move to the next argument
	}

	return 0;
}
