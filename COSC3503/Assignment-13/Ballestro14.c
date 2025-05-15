///////////////////////////////////////////////////////////////////
// Student name: Alyssa Ballestro
// Course: COSC3503
// Assignment: #13 - Client-Server FIFOs
// Source Code File name: Ballestro14.C
// Program's Purpose: Implements the client software that will send a request
//          to the server via a server FIFO and read the answer sent
//          back by the server via a FIFO set up by the client
// Program's Limitations: See the #define constants
// Assumptions: The server program uses the FIFO communication protocol that is
//              expected by this client program
// Development Computer:  Lenovo Legion 5
// Operating System: Windows 11
// Compiler: Cygwin with Notepad++
// Program's Operational Status: In Progress
///////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE  512
#define NAME_SIZE    100 
#define SERVER_FIFO_NAME "server.fifo"
#define SHUTDOWN_PHRASE "SHUTDOWN"
#define MAX_OPTION_SIZE 3
#define FALSE 0
#define TRUE 1

// Prototypes
void performClientDuties(char *clientFifoName, int shutdownRequested);


// *******************************************************
int main(int argc, char *argv[])
{
    char clientFifoName[100];
    int shutdownRequested = 0; // Flag for shutdown request

    // Parse command-line arguments
    if (argc > 2 || (argc == 2 && strcmp(argv[1], "-s") != 0)) {
        fprintf(stderr, "Usage: %s [-s]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2 && strcmp(argv[1], "-s") == 0) {
        shutdownRequested = 1;
    }

    // Create the client FIFO name based on the process ID
    pid_t pid = getpid(); // Get process ID
    sprintf(clientFifoName, "client-%d.fifo", pid); // Generate FIFO name

    // Create the FIFO
    if (mkfifo(clientFifoName, 0666) == -1) {
        if (errno == EEXIST) {
            fprintf(stderr, "CLIENT: An existing client FIFO has been detected: %s\n", clientFifoName);
        } else {
            perror("CLIENT: Error creating the client FIFO");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("CLIENT: The client FIFO named %s has been created\n", clientFifoName);
    }
	// Perform client duties
    performClientDuties(clientFifoName, shutdownRequested);
	
	// Exit/Close/Terminate the FIFO
    printf("CLIENT: PID# %d has terminated\n", getpid());
    return 0;

return 0;
} // End main


// ********************************************************************
void performClientDuties(char *clientFifoName, int shutdownRequested) {
    char requestBuffer[BUFFER_SIZE];
    char responseBuffer[BUFFER_SIZE];
    int serverFifoId, clientFifoId;

    // Open the server FIFO in write mode
    serverFifoId = open(SERVER_FIFO_NAME, O_WRONLY);
	
    if (serverFifoId == -1) {
        perror("CLIENT: Error opening the server FIFO in write mode");
        exit(EXIT_FAILURE);
    }

    // Prepare the request (PID or SHUTDOWN)
    if (shutdownRequested) {
        strcpy(requestBuffer, SHUTDOWN_PHRASE);
    } else {
        sprintf(requestBuffer, "%d", getpid());
    }

    // Send the request to the server
    if (write(serverFifoId, requestBuffer, strlen(requestBuffer)) == -1) {
        perror("CLIENT: Error writing to the server FIFO");
        close(serverFifoId);
        exit(EXIT_FAILURE);
    }
    printf("CLIENT: Sent request to the server: %s\n", requestBuffer);

    // Close the server FIFO
    close(serverFifoId);

    if (!shutdownRequested) {
        // Open the client FIFO in read mode
        clientFifoId = open(clientFifoName, O_RDONLY);
        if (clientFifoId == -1) {
            perror("CLIENT: Error opening the client FIFO in read mode");
            exit(EXIT_FAILURE);
        }

        printf("CLIENT: Waiting for a response from the server...\n");

        // Read the response from the client FIFO
        ssize_t bytesRead = read(clientFifoId, responseBuffer, BUFFER_SIZE - 1);
        if (bytesRead == -1) {
            perror("CLIENT: Error reading from the client FIFO");
            close(clientFifoId);
            exit(EXIT_FAILURE);
        }

        responseBuffer[bytesRead] = '\0'; // Null-terminate the response
        printf("CLIENT: Received response from server: %s\n", responseBuffer);

        // Close the client FIFO
        close(clientFifoId);
    } else {
        printf("CLIENT: Shutdown request sent. No response expected.\n");
    }

    // Cleanup/Unlink Fifo
    if (unlink(clientFifoName) == -1) {
        perror("CLIENT: Error unlinking the client FIFO");
        exit(EXIT_FAILURE);
    }
    printf("CLIENT: The client FIFO %s has been removed\n", clientFifoName);
}