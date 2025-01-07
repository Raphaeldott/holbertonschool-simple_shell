#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "simple-shell.h"

/**
 * tokenize_input - Split the input line into command and arguments.
 * @line: The input line to tokenize.
 *
 * Return: An array of strings (tokens), NULL-terminated.
 */
char **tokenize_input(char *line)
{
	size_t bufsize = 64, i = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " ");
	while (token)
	{
		tokens[i++] = token;
		if (i >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
 * prompt - Displays a prompt, reads user input, and executes commands.
 *
 * This function prints a prompt to the terminal, reads a line of input from
 * the user, and processes the input. It processes the input by
 * attempting to execute the command using the execve system call. If the
 * command cannot be executed, it prints an error message. The function handles
 * errors from getline and ensures that memory is properly managed. It also
 * handles the end-of-file condition (Ctrl+D) to exit gracefully. The function
 * runs in an infinite loop, repeatedly prompting the user for input until
 * terminated.
 */
void prompt(void)
{
	char *input_line = NULL;
	size_t input_length = 0;
	ssize_t characters_read;
	char **argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_prompt();
		characters_read = read_input(&input_line, &input_length);
		if (characters_read == -1)
		{
			free(input_line);
			exit(EXIT_FAILURE);
		}

		input_line[strcspn(input_line, "\n")] = '\0'; /* Remove newline */
		handle_exit(input_line);  /* Handle "exit" command */
		handle_env(input_line);   /* Handle "env" command */
		argv = tokenize_input(input_line);
		execute_command(argv, environ);
		free(argv);
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
	prompt();
	return (0);
}
