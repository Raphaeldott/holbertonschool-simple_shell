#include "simple-shell.h"

/**
 * read_input - Read a line of input from the user.
 * @line: Pointer to the buffer where the input will be stored.
 * @length: Pointer to the size of the buffer.
 *
 * Return: The number of characters read, or -1 on failure.
 *
 * This function reads a line of input from the user using the
 * getline function.
 * It handles errors and end-of-file conditions appropriately.
 */
ssize_t read_input(char **line, size_t *length)
{
	ssize_t read = getline(line, length, stdin);

	if (read == -1)
	{
		if (*line == NULL) /* EOF detected */
		{
			printf("\n");
			free(*line);
			exit(0);
		}
		else
		{
			perror("getline");
			free(*line);
			exit(EXIT_FAILURE);
		}
	}
	if (*line && (*line)[0] == 27)
	{
		memset(*line, 0, strlen(*line));
		return (0);
	}
	if ((*line)[read - 1] == '\n')
		(*line)[read - 1] = '\0';
	return (read);
}

/**
 * handle_exit - Checks if the input command is "exit" and exits the shell.
 * @input_line: The input command entered by the user.
 *
 * This function checks if the input command is "exit". If it is, the function
 * frees the input line buffer and exits the shell.
 */
void handle_exit(char *input_line)
{
	if (strcmp(input_line, "exit") == 0)
	{
		free(input_line);
		exit(0);
	}
	}

/**
 * handle_env - Prints the current environment variables.
 * @input_line: The input command entered by the user.
 *
 * This function checks if the input command is "env". If it is, the function
 * prints the current environment variables.
 */
void handle_env(char *input_line)
{
	if (strcmp(input_line, "env") == 0)
	{
		char **env;

		for (env = environ; *env != NULL; env++)
		{
			printf("%s\n", *env);
		}
	}
}
