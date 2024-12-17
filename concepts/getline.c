#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *line = NULL;  // Pointer to hold the input line
    size_t len = 0;     // Variable to store buffer size

    while (1) {
        printf("$ ");                     // Print the prompt
        ssize_t nread = getline(&line, &len, stdin);  // Read input

        if (nread == -1) {  // Check for EOF (Ctrl+D)
            printf("\n");   // Print a newline for clean exit
            break;
        }

        printf("%s", line); // Print the entered command
    }

    free(line);  // Free the allocated memory
    return 0;
}
