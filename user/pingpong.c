#include "user/user.h"
#include "kernel/types.h"

int main(void) {
    int parentPipe[2]; // Parent to Child's pipe
    int childPipe[2]; // Child to Parent's pipe
    char buffer; // Buffer to contain the send byte
    char msg = 'x'; // Random character to send

    // Initialize pipes
    pipe(parentPipe);
    pipe(childPipe);

    int processID = fork(); // Initialize a new process

    if (processID == 0) { // Child's process

        // Read a byte sent from parent
        read(parentPipe[0], &buffer, sizeof(buffer));

        // Inform that child's process has received the byte
        printf("%d: received ping\n", getpid());

        // Write back the byte to parent's process
        write(childPipe[1], &msg, sizeof(msg));

        // Child exits
        exit(0);
    } else { // Parent's process

        // Write the byte into the pipe and send to child
        write(parentPipe[1], &msg, sizeof(msg));

        // Receive the byte that child sends back
        read(childPipe[0], &buffer, sizeof(buffer));

        // Inform that parent's process has received the byte
        printf("%d: received pong\n", getpid());

        // Wait for the termination of child's process
        wait(0);
    }

    // Parent exits
    exit(0);
}