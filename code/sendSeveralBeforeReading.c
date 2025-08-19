#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    if (pid == 0) {
        pid_t childPID = getpid();
        char message[100];
        printf("Child. PID, %d.\n", (int) childPID);
        close(fd[0]);

        for (int i = 0; i < 3; i++) {
            snprintf(message, sizeof(message), "Hello %d from a child.", i);
            write(fd[1], message, strlen(message) + 1);
        }

        close(fd[1]);
        _exit(0);
    } else {
        wait(NULL);
        printf("Parent. PID, %d.\n", (int) getpid());
        close(fd[1]);
        char buffer[100];
        ssize_t numBytes = read(fd[0], buffer, sizeof(buffer));
        read(fd[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);
        printf("The length of a message, including the null terminator, is %ld.\n", strlen(buffer) + 1);
        printf("The overall length of everything in the pipe is %zd.\n", numBytes);

        // for (int i = 0; i < 3; i++) {
        //     read(fd[0], buffer, strlen("Hello 0 from a child.") + 1);
        //     printf("%s\n", buffer);
        // }

        close(fd[0]);
    }

    return 0;
}