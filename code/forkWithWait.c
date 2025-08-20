#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("Hello, world. PID, %d.\n", (int) getpid()); //Print the default PID, which is the parent's.
    int rc = fork(); //Create a fork.

    if (rc < 0) {
        fprintf(stderr, "Fork failed.\n");
        exit(1); //Exit if fork failed.
    } else if (rc == 0) {
        printf("Hello, I am a child. PID, %d.\n", (int) getpid()); //Print the child's PID if on the child process.
    } else {
        int wc = wait(NULL); //Wait for the child to finish processing.
        printf("Hello, I am a parent of %d. WC, %d. PID, %d.\n", rc, wc, (int) getpid()); //Print the parent's PID if on the parent process.
    }

    return 0;
}