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
        sleep(1); //Sleep for 1 second.
        printf("Hello, I am a child. PID, %d.\n", (int) getpid()); //Print the child's PID.
    } else {
        sleep(5); //Sleep longer for 5 seconds to die later than the child. Switch the argument to die before the child.
        printf("Hello, I am a parent of %d. PID, %d.\n", rc, (int) getpid()); //Print the parent's PID.
    }

    return 0;
}