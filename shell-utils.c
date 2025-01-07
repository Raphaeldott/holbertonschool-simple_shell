#include "simple-shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * is_absolute_command - Checks if a command is an absolute or relative path.
 * @command: The command to check.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_absolute_command(char *command)
{
	return (command[0] == '/' || command[0] == '.');
}

/**
 * check_absolute_command - Checks if an absolute/relative path is executable.
 * @command: The command to check.
 *
 * Return: The duplicated command if executable, NULL otherwise.
 */
char *check_absolute_command(char *command)
{
	if (access(command, X_OK) == 0)
		return (strdup(command));

	fprintf(stderr, "%s: Command not found\n", command);
	return (NULL);
}

/**
 * search_in_path - Searches for a command in PATH directories.
 * @command: The command to search for.
 * @path: The PATH environment variable.
 *
 * Return: The full path to the executable if found, NULL otherwise.
 */
char *search_in_path(char *command, char *path)
{
	char *path_copy = strdup(path), *dir, *full_path = malloc(1024);

	if (!path_copy || !full_path)
	{
		perror("Memory allocation failed");
		free(path_copy);
		free(full_path);
		return (NULL);
	}

	dir = strtok(path_copy, ":");
	while (dir)
	{
		snprintf(full_path, 1024, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	free(full_path);
	return (NULL);
}

/**
 * find_executable - Finds the full path of an executable command.
 * @command: The command to find.
 *
 * Return: The full path to the executable if found, NULL otherwise.
 */
char *find_executable(char *command)
{
	char *path;

	if (!command || !*command)
	{
		return (NULL);
	}

	if (is_absolute_command(command))
	{
		return (check_absolute_command(command));
	}

	path = getenv("PATH");
	if (!path)
	{
		return (NULL);
	}
	return (search_in_path(command, path));
}

/**
 * execute_command - Executes a command entered by the user.
 * @argv: Array of command arguments.
 * @environment_var: The environment variables.
 *
 * This function forks a child process to execute the
 * command entered by the user. The child process uses
 * execve to run the command. The parent process waits
 * for the child to finish. If execve fails, an error
 * message is printed.
 */
void execute_command(char **argv, char **environment_var)
{
	pid_t pid;
	char *executable;

	if (argv == NULL || argv[0] == NULL)
	{
		fprintf(stderr, "No such file or directory\n");
		exit(1);
	}

	executable = find_executable(argv[0]);
	if (executable == NULL)
	{
		fprintf(stderr, "%s: No such file or directory\n", argv[0]);
		exit(1);
	}

	argv[0] = executable;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(executable);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)  /* Child process */
	{
		if (execve(argv[0], argv, environment_var) == -1)
		{
			perror(argv[0]);
			free(executable);
			exit(EXIT_FAILURE);
		}
	}
	else  /* Parent process */
	{
		wait(NULL);
	}

	free(executable);
}
