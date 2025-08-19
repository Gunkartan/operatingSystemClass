#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("Hello, world. PID, %d.\n", (int) getpid());
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "Fork failed.\n");
        exit(1);
    } else if (rc == 0) {
        printf("Hello, I am a child. PID, %d.\n", (int) getpid());
    } else {
        int wc = wait(NULL);
        printf("Hello, I am a parent of %d. WC, %d. PID, %d.\n", rc, wc, (int) getpid());
    }

    return 0;
}