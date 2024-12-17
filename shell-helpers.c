#include "simple-shell.h"

/**
 * print_prompt - Displays the prompt to the user.
 *
 * This function prints the shell prompt to the terminal, 
 * indicating that the shell is ready to accept a new command
 * from the user.
 */
void print_prompt(void)
{
	printf("My_Shell$ ");
}

/**
 * read_input - Reads a line of input from the user.
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
		if (feof(stdin))
		{
			printf("\n");
			free(*line);
			exit(0);
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
 * @command: The command to execute.
 * @environment_var: The environment variables.
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
 * handle_exit - Checks if the input command is "exit" and
 * exits the shell.
 * @input_line: The input command entered by the user.
 *
 * This function checks if the input command is "exit". 
 * If it is, the function frees the input line buffer
 * and exits the shell.
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
 * This function checks if the input command is "env".
 * If it is, the function prints the current environment variables.
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
