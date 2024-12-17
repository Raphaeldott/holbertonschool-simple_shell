#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Parent Process ID: %d\n", getppid());
    return 0;
}
