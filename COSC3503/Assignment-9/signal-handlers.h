///////////////////////////////////////////////////////////////////
// Student name: Instructor
// Course: COSC 3503
// Assignment: #9 - POSIX Signals
// Source Code File Name: signal-handlers.h
// Program's Purpose: Provides the #define constants and function prototypes
//          for the signal handler functions
// Assumptions: See the main test driver file  
// Program's Limitations: None
// 
// Development Computer: Dell 
// Operating System: Windows 7 using CYGWIN
// Compiler: Gnu gcc
// Build Directions: See the driver module
// Program's Operational Status: Fullfills the requirements
///////////////////////////////////////////////////////////////////

#ifndef SIGNAL_HANDLERS_HEADER
#define SIGNAL_HANDLERS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// Function Prototypes
void registerSignalHandlers(void);

#endif

