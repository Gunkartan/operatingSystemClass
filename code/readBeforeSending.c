#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd); //Create a pipe.
    pid_t pid = fork(); //Create a fork.

    if (pid == 0) {
        pid_t childPID = getpid(); //Get the child's PID.
        char message[100];
        snprintf(message, sizeof(message), "Hello from a child. PID, %d.", (int) childPID); //Create a message.
        printf("Child. PID, %d.\n", (int) childPID); //Print the child's PID.
        sleep(3); //Sleep for 3 seconds to wait for the parent to read the message before sending.
        close(fd[0]);
        write(fd[1], message, strlen(message) + 1); //Write the message by closing the read end first. Close the write end after finishing.
        close(fd[1]);
        _exit(0);
    } else {
        printf("Parent. PID, %d.\n", (int) getpid()); //Print the parent's PID.
        close(fd[1]);
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer)); //Read the message by closing the write end first. Close the read end after finishing.
        printf("%s\n", buffer); //Print the message.
        close(fd[0]);
    }

    return 0;
}