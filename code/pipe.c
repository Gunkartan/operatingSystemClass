#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    if (pid == 0) {
        pid_t childPID = getpid();
        printf("Child. PID, %d.\n", (int) childPID);
        close(fd[0]);
        char message[] = "Hello from a child.";
        write(fd[1], &childPID, sizeof(childPID));
        close(fd[1]);
        _exit(0);
    } else {
        printf("Parent. PID, %d.\n", (int) getpid());
        close(fd[1]);
        char buffer[100];
        pid_t receivedPID;
        read(fd[0], &receivedPID, sizeof(receivedPID));
        printf("%d\n", (int) receivedPID);
        close(fd[0]);
    }

    return 0;
}