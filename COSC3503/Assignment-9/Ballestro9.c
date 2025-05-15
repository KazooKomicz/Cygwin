// Student name: Alyssa Ballestro
// Course: COSC 3503 - Operating Systems
// Assignment: #9 - Signal Handling
// Source Code File Name: 
// Program's Purpose: Provides the definitions for the functions that search a word puzzle file
// Program's Limitations: See the limitation comments in the puzzleSearcher.h file
// Development Computer: Lenovo Legion 5
// Operating System: Windows 11
// Compiler: Notepad++
// Build Instructions: See the driver module
// Operational Status: In Progress
///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "signal-handlers.h"

// Define each signal handler function
void handleSIGABRT(int sig) {
    printf("Assertion failed: program will now end (SIGABRT received).\n");
    exit(EXIT_FAILURE);
}

void handleSIGALRM(int sig) {
    printf("Allowable time expired: program will now end (SIGALRM received).\n");
    exit(EXIT_FAILURE);
}

void handleSIGCHLD(int sig) {
    pid_t child_pid = wait(NULL);
    if (child_pid > 0) {
        printf("Received wait call from child process #%d (SIGCHLD received).\n", child_pid);
    }
}

void handleSIGFPE(int sig) {
    printf("Critical arithmetic error occurred: program will now end (SIGFPE received).\n");
    exit(EXIT_FAILURE);
}

void handleSIGINT(int sig) {
    printf("Program detected the <Control C> key (SIGINT received). Returning to regular processing.\n");
}

void handleSIGSEGV(int sig) {
    printf("Critical memory access error occurred: program will now end (SIGSEGV received).\n");
    exit(EXIT_FAILURE);
}

void handleSIGTERM(int sig) {
    printf("Program received a request to terminate: program will now end (SIGTERM received).\n");
    exit(EXIT_FAILURE);
}

// Register the signal handlers
void registerSignalHandlers() {
    if (signal(SIGABRT, handleSIGABRT) == SIG_ERR) {
        perror("Error registering SIGABRT handler");
    }
    if (signal(SIGALRM, handleSIGALRM) == SIG_ERR) {
        perror("Error registering SIGALRM handler");
    }
    if (signal(SIGCHLD, handleSIGCHLD) == SIG_ERR) {
        perror("Error registering SIGCHLD handler");
    }
    if (signal(SIGFPE, handleSIGFPE) == SIG_ERR) {
        perror("Error registering SIGFPE handler");
    }
    if (signal(SIGINT, handleSIGINT) == SIG_ERR) {
        perror("Error registering SIGINT handler");
    }
    if (signal(SIGSEGV, handleSIGSEGV) == SIG_ERR) {
        perror("Error registering SIGSEGV handler");
    }
    if (signal(SIGTERM, handleSIGTERM) == SIG_ERR) {
        perror("Error registering SIGTERM handler");
    }
}