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
void handle_exit(char *input_line);
void handle_env(char *input_line);
void shell_loop(void);
char *find_executable(char *command);
void execute_command(char **argv, char **environment_var);
char **tokenize_input(char *line);
void prompt(void);
int is_absolute_command(char *command);
char *check_absolute_command(char *command);
char *search_in_path(char *command, char *path);


#endif /* SHELL_H */
