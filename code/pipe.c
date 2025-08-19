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
        snprintf(message, sizeof(message), "Hello from a child. PID %d.", (int) childPID);
        printf("Child. PID, %d.\n", (int) childPID);
        close(fd[0]);
        write(fd[1], message, strlen(message) + 1);
        close(fd[1]);
        _exit(0);
    } else {
        wait(NULL);
        printf("Parent. PID, %d.\n", (int) getpid());
        close(fd[1]);
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);
        close(fd[0]);
    }

    return 0;
}