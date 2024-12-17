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
void prompt(void);
void handle_exit(char *input_line);

#endif /* SHELL_H */
