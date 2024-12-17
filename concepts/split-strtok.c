#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *token;

	// Check if a string was passed as an argument
	if (argc < 2)
	{
		printf("Usage: %s \"string to tokenize\"\n", argv[0]);
		return 1;
	}

	printf("Original string: \"%s\"\n", argv[1]);
	printf("Tokens:\n");

	// Tokenize the first argument using delimiters
	token = strtok(argv[1], " ,?"); // Delimiters: space, comma, and question mark
	while (token != NULL)
	{
		printf("Token: %s\n", token);
		token = strtok(NULL, " ,?"); // Get the next token
	}

	return 0;
}
