#include <stdlib.h>
#include <stdio.h>

char **split_string(char *str, char *delim)
{
	char **tokens, *start;
	int i = 0, word = 0;

	if (!str || !*str)
		return (NULL);

	tokens = malloc(100 * sizeof(char *));
	if (!tokens)
		return (NULL);

	while (*str)
	{
		if (!strchr(delim, *str) && word == 0)
		{
			start = str;
			word = 1;
		}
		if ((strchr(delim, *str) || *(str + 1) == '\0') && word)
		{
			tokens[i] = malloc((str - start) + 2);
			if (!tokens[i])
				return (NULL);
			strncpy(tokens[i], start, (str - start) + 1);
			tokens[i++][(str - start) + 1] = '\0';
			word = 0;
		}
		str++;
	}
	tokens[i] = NULL;
	return (tokens);
}

int main(void)
{
	char input[] = "Hello,   this is,    a test!";
	char **tokens = split_string(input, " ,!");
	int i = 0;

	while (tokens[i])
	{
		printf("Token %d: %s\n", i, tokens[i]);
		free(tokens[i++]);
	}
	free(tokens);
	return (0);
}
