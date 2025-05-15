////////////////////////////////////////////////////////////////
// Student name: Alyssa Ballestro
// Course: COSC 3503
// Assignment: 3 Sorting Algorithms
// Source Code File Name: Ballestro10.c
// Program's Purpose: Demonstrates how to do FCFS, Round Robin, and 
// Program's Limitations: The array handles up to MAX_ROWS 
// Development Computer: Dell 
// Operating System: Windows 7 running CYGWIN
// Compiler: Gnu gcc
// Program's Operational Status: Satisfies all of the requirements
////////////////////////////////////////////////////////////////

#include <stdio.h>   // For printf
#include <stdlib.h>  // For general utilities
#include <string.h>  // For string handling (if needed)
#include "scheduling-algorithms.h"

// ###################################

void scheduleFCFS(processDataType processes[], int processCount){
	int tatTime = 0;
	int waitTime = 0;
	
	printf("Process#\tStart Time\tStop Time\tRunning Time\n");
	for (int i = 0; i < processCount; i++){
		int processNum = processes[i].processNbr;
		int processTime = processes[i].totalTime; //also known as burst
		
		
		tatTime += processTime;
		processes[i].stopTime = tatTime;
		processes[i].waitSum = waitTime;
		
		printf("%-8d\t%-11d\t%-10d\t%-12d\n", processNum, processTime, waitTime, tatTime);

        // Update wait time for next process
        waitTime += processTime;
	}
	
	printf("\nAverage Waiting Time: %.2f\n", (float) waitTime / processCount);
    printf("Average Turnaround Time: %.2f\n", (float) tatTime / processCount);
}
//End FCFS
void scheduleSJF(processDataType processes[], int processCount){
	printf("Process#\tStart Time\tStop Time\tRunning Time\n");
	
	for (int i = 0; i < processCount - 1; i++){
		for (int j = 0; j < processCount - 1; j++){
			if(processes[j].totalTime > processes[j+1].totalTime) {
				processDataType temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
			}
		}
	}
	
	int waitTime = 0;
	int tatTime = 0;
	
	for (int i = 0; i < processCount; i++){
		int processNum = processes[i].processNbr;
		int processTime = processes[i].totalTime; //also known as burst
		
		
		tatTime += processTime;
		processes[i].stopTime = tatTime;
		processes[i].waitSum = waitTime;
		
		printf("%-8d\t%-11d\t%-10d\t%-12d\n", processNum, processTime, waitTime, tatTime);

        // Update wait time for next process
        waitTime += processTime;
	}
	
	printf("\nAverage Waiting Time: %.2f\n", (float) waitTime / processCount);
    printf("Average Turnaround Time: %.2f\n", (float) tatTime / processCount);
}
//End SFJ
void scheduleRoundRobin(processDataType processes[], int processCount, int quantum){
	int completedProcesses = 0;
	int tattime = 0; // Keeps track of total elapsed time
	
	printf("Process#\tStart Time\tStop Time\tRunning Time\n");
	
    while (completedProcesses < processCount) {
        for (int i = 0; i < processCount; i++) {
            // Skip finished processes
            if (processes[i].isFinished) {
                continue;
            }

            // If the process can finish within its quantum
            if (processes[i].remainingTime <= quantum) {
                tattime += processes[i].remainingTime; 
                processes[i].remainingTime = 0;     
                processes[i].stopTime = tattime;       
                processes[i].isFinished = TRUE;     
                completedProcesses++;

                // Calculate and print metrics
                int tatTime = processes[i].stopTime;            // Turnaround Time
                int waitTime = tatTime - processes[i].totalTime; // Waiting Time
                processes[i].waitSum = waitTime;

                printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i].processNbr, processes[i].totalTime, waitTime, tatTime);
            } else {
                // Process uses up its quantum
                tattime += quantum;
                processes[i].remainingTime -= quantum; // Reduce its remaining time
            }
        }
    }
	
	int tatTime = 0;
	int waitTime = 0;
	
	for (int i = 0; i < processCount; i++){
		int processNum = processes[i].processNbr;
		int processTime = processes[i].totalTime; //also known as burst
		
		
		tatTime += processTime;
		processes[i].stopTime = tatTime;
		processes[i].waitSum = waitTime;
		
		printf("%-8d\t%-11d\t%-10d\t%-12d\n", processNum, processTime, waitTime, tatTime);

        // Update wait time for next process
        waitTime += processTime;
	}
	
	printf("\nAverage Waiting Time: %.2f\n", (float) waitTime / processCount);
    printf("Average Turnaround Time: %.2f\n", (float) tatTime / processCount);
}
//End RR