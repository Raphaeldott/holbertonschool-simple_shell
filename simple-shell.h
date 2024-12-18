#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void print_prompt(void);
ssize_t read_input(char **line, size_t *len);
void execute_command(char *line, char **environ);
void handle_exit(char *input_line);
void handle_env(char *input_line);
void shell_loop(void);
char *find_executable(char *command);

#endif /* SHELL_H */
