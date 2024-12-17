#include <stdio.h>
#include <stdlib.h>

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream) {
	if (lineptr == NULL || n == NULL || stream == NULL) {
		return -1; // Invalid parameters
	}

	size_t pos = 0;
	int c;

	if (*lineptr == NULL) {  // Allocate buffer if not already allocated
		*n = 128;            // Initial size
		*lineptr = malloc(*n);
		if (*lineptr == NULL) {
			return -1;       // Allocation failure
		}
	}

	while ((c = fgetc(stream)) != EOF) {
		if (pos + 1 >= *n) {    // Resize buffer if needed
			*n *= 2;
			char *new_lineptr = realloc(*lineptr, *n);
			if (new_lineptr == NULL) {
				return -1;     // Reallocation failure
			}
			*lineptr = new_lineptr;
		}

		(*lineptr)[pos++] = c;

		if (c == '\n') {        // Stop reading on newline
			break;
		}
	}

	if (pos == 0 && c == EOF) { // No input and EOF
		return -1;
	}

	(*lineptr)[pos] = '\0';     // Null-terminate the string
	return pos;
}

int main(void) {
	char *line = NULL;
	size_t len = 0;

	while (1) {
		printf("$ ");
		ssize_t nread = custom_getline(&line, &len, stdin);

		if (nread == -1) {  // EOF
			printf("\n");
			break;
		}

		printf("%s", line);
	}

	free(line);
	return 0;
}
