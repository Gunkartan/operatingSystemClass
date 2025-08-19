#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int count = 0;

    while (1) {
        pid_t rc = fork();

        if (rc < 0) {
            printf("Fork failed after %d successful forks.\n", count);
            exit(0);
        } else if (rc == 0) {
            exit(0);
        } else {
            count++;
        }
    }

    return 0;
}