#include "simple-shell.h"

/**
 * shell_loop - Main loop of the shell.
 *
 * This function runs in an infinite loop, repeatedly prompting the user for
 * input, reading the input, and executing the command. It handles errors and
 * the end-of-file condition (Ctrl+D) to exit gracefully.
 */
void shell_loop(void)
{
	char *input_line = NULL;
	size_t input_length = 0;
	ssize_t characters_read;

	while (1)
	{
		print_prompt();
		characters_read = read_input(&input_line, &input_length);
		if (characters_read == -1)
		{
			free(input_line);
			exit(EXIT_FAILURE);
		}

		input_line[strcspn(input_line, "\n")] = '\0';
		handle_exit(input_line);
		handle_env(input_line);
		execute_command(input_line, environ);
	}

	free(input_line);
}

/**
 * main - Entry point of the shell program.
 * This function calls the shell_loop function to start the
 * shell and then returns 0 to indicate successful execution.
 *
 * Return: Always 0.
 */
int main(void)
{
	shell_loop();
	return (0);
}
