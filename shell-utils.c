#include "simple-shell.h"

/**
 * find_executable - Searches for an executable in the
 * directories listed in PATH.
 * @command: The command to search for.
 *
 * Return: The full path to the executable if found, otherwise NULL.
 */
char *find_executable(char *command)
{
	char *path, *path_copy, *dir, *full_path;

	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	full_path = malloc(1024);
	if (!full_path)
	{
		free(path_copy);
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
	char *executable = find_executable(argv[0]);

	if (executable == NULL)
	{
		fprintf(stderr, "%s: No such file or directory\n", argv[0]);
		return;
	}

	argv[0] = executable;
	argv[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(argv[0]);
		free(executable);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(argv[0], argv, environment_var) == -1)
		{
			perror(argv[0]);
			free(executable);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL); /* Wait for child process to complete */
	}

	free(executable);
}
