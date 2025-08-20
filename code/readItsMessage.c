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
        close(fd[0]);
        write(fd[1], message, strlen(message) + 1); //Write the message by closing the read end first. Close the write end after finishing.
        close(fd[1]);
        char childBuffer[100];
        read(fd[0], childBuffer, sizeof(childBuffer)); //Try to read the message after sending.
        printf("%s\n", childBuffer); //Print what was read.
        _exit(0);
    } else {
        wait(NULL); //Wait for the child to finish processing.
        printf("Parent. PID, %d.\n", (int) getpid()); //Print the parent's PID.
        close(fd[1]);
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer)); //Read the message by closing the write end first. Close the read end after finishing.
        printf("%s\n", buffer); //Print the message.
        close(fd[0]);
    }

    return 0;
}