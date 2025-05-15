///////////////////////////////////////////////////////////////////
// Student name:  
// Course: COSC 3503 - Operating Systems
// Assignment: #6 - Multiple Processes
// Source Code File name:  Ballestro6
// Program's Purpose: Provides the functionality that searches the list for the
//          maximum integer value with the help of 1 or more child
//          processes
// Program's Limitations: Because a child process can only return a value up
//       to 255, the largest possible integer in the list cannot exceed 255
// Development Computer:   Lenovo Legion 5
// Operating System:  Windows 11
// Compiler:  Notepad++
// Build Instructions: See the driver module
// Program's Operational Status:  In Process
///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "listSearcher.h"

// Function Prototypes
static int findMaxInteger(int list[], int startingIndex, int numbrOfEntries);


void searchIntegerList(int list[], int nbrOfListEntries, int childrenCount)
{
    int strtinx = 0;
    int grpSize = nbrOfListEntries / childrenCount;
    pid_t pid;

    for (int i = 0; i < childrenCount; i++) {
        if (i == childrenCount - 1) {
            grpSize = nbrOfListEntries - strtinx; // Adjust last group size
        }

        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            int maxVal = findMaxInteger(list, strtinx, grpSize);
            exit(maxVal); // Return max value as exit status
        } else {
            strtinx += grpSize; // Parent increments starting index
        }
    }
    return; // Results are handled by the driver through wait() calls
}



static int findMaxInteger(int list[], int startingIndex, int nbrOfEntries)
{
    if (nbrOfEntries <= 0) {
        fprintf(stderr, "(Child process %d) Error: Empty range provided\n", getpid());
        return -1;
    }

    int maxInteger = list[startingIndex]; // Initialize max with the first element
    int stoppingIndex = startingIndex + nbrOfEntries;
    
    printf("(Child process %d) Searching in range [%d, %d): ", getpid(), startingIndex, stoppingIndex);
    
    for (int i = startingIndex + 1; i < stoppingIndex; i++) {
        if (list[i] > maxInteger) {
            maxInteger = list[i];
        }
    }
    
    printf("Max integer found: %d\n", maxInteger);
    return maxInteger;
} // End findMaxInteger



