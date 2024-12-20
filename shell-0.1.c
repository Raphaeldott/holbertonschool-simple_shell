#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "simple-shell.h"

extern char **environ;

/**
 * print_prompt - Displays the prompt to the user.
 */
void print_prompt(void)
{
	printf("My_Shell$ ");
}

/**
 * read_input - Reads a line of input from the user.
 * @line: Pointer to the buffer where the input will be stored.
 * @len: Pointer to the size of the buffer.
 *
 * Return: The number of characters read, or -1 on failure.
 */
ssize_t read_input(char **line, size_t *length)
{
	ssize_t read = getline(line, length, stdin);

	if (read == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
		}
		else
		{
			perror("getline");
		}
	}
	return (read);
}

/**
 * tokenize_input - Splits the input line into command and arguments.
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
 * execute_command - Executes the command entered by the user.
 * @argv: Array of command and arguments.
 * @environ: The environment variables.
 */
void execute_command(char **argv, char **environment_var)
{
	pid_t pid;

	if (!argv || !argv[0])
		return;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(argv[0], argv, environment_var) == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}

/**
 * prompt - Displays a prompt, reads user input, and executes commands.
 */
void prompt(void)
{
	char *input_line = NULL;
	size_t input_length = 0;
	ssize_t characters_read;
	char **argv;

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
		argv = tokenize_input(input_line);
		execute_command(argv, environ);
		free(argv);
	}

	free(input_line);
}

/**
 * main - Entry point of the shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	prompt();
	return (0);
}
