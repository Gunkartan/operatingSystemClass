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
        printf("Child. PID, %d.\n", (int) childPID); //Print the child's PID.
        close(fd[0]);

        for (int i = 0; i < 3; i++) { //Send a message 3 times.
            snprintf(message, sizeof(message), "Hello %d from a child.", i); //Create a message.
            write(fd[1], message, strlen(message) + 1); //Write the message by closing the read end first. Close the write end after finishing.
        }

        close(fd[1]);
        _exit(0);
    } else {
        wait(NULL); //Wait for the child to finish processing.
        printf("Parent. PID, %d.\n", (int) getpid()); //Print the parent's PID.
        close(fd[1]);
        char buffer[100];
        // read(fd[0], buffer, sizeof(buffer));
        // printf("%s\n", buffer);

        for (int i = 0; i < 3; i++) { //Read a message 3 times.
            read(fd[0], buffer, strlen("Hello 0 from a child.") + 1); //Read the message by closing the write end first. Close the read end after finishing.
            printf("%s\n", buffer); //Print the message.
        }

        close(fd[0]);
    }

    return 0;
}