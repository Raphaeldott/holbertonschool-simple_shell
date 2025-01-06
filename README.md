# Simple Shell

## Description

**Simple Shell** is a custom UNIX shell implementation written in C. It provides a simple command-line interface to execute commands, similar to `/bin/sh`. This project is built for educational purposes to understand and demonstrate how shells work internally.

---

## Features

- **Basic Command Execution**: Executes commands with or without arguments (e.g., `/bin/ls`, `ls -l`).
- **PATH Handling**: Searches for executables in directories listed in the `PATH` environment variable.
- **Built-in Commands**:
  - `exit`: Exits the shell.
  - `env`: Prints the current environment variables.
- **Error Handling**:
  - Prints an error message if the command is not found.
  - Handles invalid inputs gracefully.
- **Memory Management**: Ensures no memory leaks occur.

---

## Usage

## Compilation
gcc -Wall -Werror -Wextra -pedantic *.c -o simple_shell

run the shell:

./simple_shell

## Exemple Commands

My_Shell$ ls
file1  file2  directory
My_Shell$ /bin/ls -l
-rw-r--r-- 1 user group 1234 Jan 1 12:00 file1
-rw-r--r-- 1 user group 5678 Jan 1 12:01 file2
My_Shell$ env
USER=username
HOME=/home/username
PATH=/usr/local/bin:/usr/bin:/bin
My_Shell$ exit

## Files
Core Files

shell-0.1.c: Contains the main loop of the shell and command processing logic.
shell-helpers.c: Helper functions for input reading, prompt display, and built-in commands.
shell-utils.c: Utility functions for finding executables and executing commands.
simple-shell.h: Header file containing function prototypes and necessary includes.

Supporting Files

Makefile: Automates the compilation process.
README.md: Documentation for the project.
AUTHORS: List of contributors.
