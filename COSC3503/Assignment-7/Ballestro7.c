///////////////////////////////////////////////////////////////////
// Student name: Alyssa Ballestro
// Course: COSC 3503 - Operating Systems
// Assignment: #7 - Unbuffered Input and Output
// Source Code File name: commentRemover.c
// Program's Purpose: Removes all of the single-line comments from a C, C++, or
//    Java text file and produces an output file with "nc" appended to the front
//    of the file name. The program obtains the option "-s" or "-p" from the
//    command line followed by one or more file names. Each file on the 
//    command line is processed by the program either sequentially or in
//    parallel. For the parallel approach, a separate forked process
//    performs the comment removal steps and a single parent process waits
//    for all children to complete  
// Program's Limitations: It assumes the input files are text files and that the 
//    operating system allows a program to have as many child processes
//    running as the number of files entered on the command line 
// Development Computer: Lenovo Legion 5
// Operating System: Windows 11
// Compiler: Notepad++
// Program's Operational Status: In Progress
///////////////////////////////////////////////////////////////////

#include "commentRemover.h"
#include <errno.h>

#define GENERAL_BUFFER_SIZE 100
#define WRITE_BUFFER_SIZE 1
#define SLASH '/'
#define NEW_LINE '\n'
#define FALSE 0
#define TRUE  1

// Function Prototypes
static void processInputFile(const char *inputFileName);
static void removeComments(int inputFile, int outputFile);

// ################################################################
void performSequentialProcessing(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {  // Start from 1 to skip the program name
        processInputFile(argv[i]);
    }
} // End performSequentialProcessing

// ################################################################
void performParallelProcessing(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {  // Start from 1 to skip the program name
        pid_t pid = fork();
        if (pid < 0) {
            perror("Error creating child process");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {  // Child process
            processInputFile(argv[i]);
            exit(EXIT_SUCCESS);  // Terminate child process
        }
        // Parent process: continue to next iteration
    }

    // Parent waits for all child processes to finish
    while (wait(NULL) > 0);
} // End performParallelProcessing

// ################################################################
static void processInputFile(const char *inputFileName)
{
    // Open the input file in read-only mode
    int inputFile = open(inputFileName, O_RDONLY);
    if (inputFile == -1) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    // Construct output file name
    char outputFileName[256];
    snprintf(outputFileName, sizeof(outputFileName), "nc-%s", inputFileName);

    // Open the output file in write mode
    int outputFile = open(outputFileName, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (outputFile == -1) {
        perror("Error opening output file");
        close(inputFile);
        exit(EXIT_FAILURE);
    }

    // Print process details
    printf("Process ID: %d, Input File: %s, Output File: %s\n", getpid(), inputFileName, outputFileName);

    // Remove comments from input and write to output
    removeComments(inputFile, outputFile);

    // Close files
    close(inputFile);
    close(outputFile);
} // End processInputFile

// ################################################################
static void removeComments(int inputFile, int outputFile)
{
    char buffer[GENERAL_BUFFER_SIZE];
    ssize_t bytesRead;
    int insideComment = FALSE;

    while ((bytesRead = read(inputFile, buffer, GENERAL_BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytesRead; i++) {
            if (!insideComment) {
                // Check for comment start
                if (buffer[i] == SLASH && (i + 1 < bytesRead && buffer[i + 1] == SLASH)) {
                    insideComment = TRUE;
                    i++;  // Skip the next '/' character
                } else {
                    // Write non-comment characters
                    ssize_t nbrBytesWritten = write(outputFile, &buffer[i], WRITE_BUFFER_SIZE);
                    if (nbrBytesWritten == -1) {
                        perror("Error writing to output file");
                        close(inputFile);
                        close(outputFile);
                        exit(EXIT_FAILURE);
                    }
                }
            } else {
                // Inside comment: look for newline to end comment
                if (buffer[i] == NEW_LINE) {
                    insideComment = FALSE;
                    // Write newline to maintain line count
                    ssize_t nbrBytesWritten = write(outputFile, &buffer[i], WRITE_BUFFER_SIZE);
                    if (nbrBytesWritten == -1) {
                        perror("Error writing to output file");
                        close(inputFile);
                        close(outputFile);
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
    }

    if (bytesRead == -1) {
        perror("Error reading input file");
        close(inputFile);
        close(outputFile);
        exit(EXIT_FAILURE);
    }
} // End removeComments
