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
	char *path = getenv("PATH");
	char *path_copy;
	char *dir;
	char *full_path;

	if (path == NULL)
	{
		return (NULL);
	}

	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		return (NULL);
	}

	full_path = malloc(1024);
	if (full_path == NULL)
	{
		free(path_copy);
		return (NULL);
	}

	dir = strtok(path_copy, ":");
	while (dir != NULL)
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
	char *executable = find_executable(command);

	if (executable == NULL)
	{
		fprintf(stderr, "%s: command not found\n", command);
		return;
	}

	argv[0] = executable;
	argv[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(command);
		free(executable);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(argv[0], argv, environment_var) == -1)
		{
			perror("./shell");
			free(executable);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}

	free(executable);
}
