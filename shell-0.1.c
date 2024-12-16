#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simple-shell.h"

/**
 * print_prompt - Displays the prompt to the user.
 *
 * This function prints the shell prompt to the terminal, indicating that the
 * shell is ready to accept a new command from the user.
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
 * execute_command - Executes the command entered by the user.
 * @line: The command to execute.
 * @environ: The environment variables.
 *
 * This function forks a child process to execute the
 * command entered by the user.
 * The child process uses execve to run the command.
 * The parent process waits for the child to finish.
 * If execve fails, an error message is printed.
 */
void execute_command(char *command, char **environment_var)
{
	char *argv[2];
	pid_t pid;

	argv[0] = command;
	argv[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(command);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(argv[0], argv, environment_var) == -1)
		{
			perror("./shell");
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
		execute_command(input_line, environ);
	}

	free(input_line);
}

/**
 * main - Entry point of the shell program.
 * This function calls the prompt function to start the
 * shell and then returns 0 to indicate successful execution.
 *
 * Return: Always 0.
 */
int main(void)
{
	prompt();
	return (0);
}
