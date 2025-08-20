#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int count = 0;

    while (1) { //Keep forking until the limit.
        pid_t rc = fork(); //Create a fork.

        if (rc < 0) {
            printf("Fork failed after %d successful forks.\n", count);
            exit(0); //Exit if fork failed.
        } else if (rc == 0) {
            exit(0); //Exit if being on the child's process.
        } else {
            count++; //Keep counting if on the parent's process.
        }
    }

    return 0;
}