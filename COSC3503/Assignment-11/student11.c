///////////////////////////////////////////////////////////////////
// Student name: 
// Course: COSC 3503
// Assignment: #11 - Traffic Simulation
// Source Code File name: 
// Program's Purpose: Uses a semaphore and threads
//    to simulate traffic synchronization at an n-way stop intersection                 
// Program's Limitations: None known
// Development Computer: 
// Operating System: 
// Compiler: 
// Build Instructions: 
// Program's Operation Status: 
///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <pthread.h>   
#include <semaphore.h>

#define TRUE  1
#define FALSE 0

// Global variables
sem_t semaphore;
int carCreationCounter = 0;
int carCompletionCounter = 0;

// Function Prototypes 
int parseCommandLine(int argc, char *argv[], int *nbrOfStopSignsPtr,
                     int *maximumCarsPtr, int *maximumTraversalTimePtr);
void displayUsageMessage(void); 
void manageTrafficSimulation(int nbrOfStopSigns, int maximumCars, 
                             int maximumTraversalTime);
void *createCar(void *maxTraversalTimePtr);


// ********************************************************
int main(int argc, char *argv[])
{
int nbrOfStopSigns;
int maximumCars;
int maximumTraversalTime;

if (!parseCommandLine(argc, argv, &nbrOfStopSigns, 
     &maximumCars, &maximumTraversalTime) )
   return 1;   

manageTrafficSimulation(nbrOfStopSigns, maximumCars, maximumTraversalTime);

return 0;
} // End main


// ****************************************************************
int parseCommandLine(int argc, char *argv[], int *nbrOfStopSignsPtr,
                     int *maximumCarsPtr, int *maximumTraversalTimePtr) 
{
int nbrOfStopSigns;
int maximumCars;
int maximumTraversalTime;

if (argc != 4)
   {
   displayUsageMessage();
   return FALSE;
   }
else
   {
   nbrOfStopSigns = atoi(argv[1]);
   maximumCars = atoi(argv[2]);
   maximumTraversalTime = atoi(argv[3]);
   } // End else

if ( (nbrOfStopSigns <= 0) || (maximumCars <= 0) ||
     (maximumTraversalTime <= 0) )
   {
   displayUsageMessage();
   return FALSE;
   } // End else
else
   {
   *nbrOfStopSignsPtr = nbrOfStopSigns;
   *maximumCarsPtr = maximumCars;
   *maximumTraversalTimePtr = maximumTraversalTime;
   return TRUE;
   } // End else

} // End parseCommandLine


// ****************************************************************
void displayUsageMessage(void)
{
printf("\nUsage: a.out <#stop signs> <#cars> <traversal time>\n\n");
printf("   <#stop signs>    - Number of stop signs at the intersection\n");
printf("   <#cars>          - Maximum number of cars to traverse the intersection\n");
printf("   <traversal time> - Maximum time (in secs) to traverse the intersection\n");
printf("\n");
printf("Note: All values should be greater than zero\n");
} // End displayUsageMessage


// *****  MAKE NO SOURCE CODE CHANGES ABOVE THIS LINE *****


// ****************************************************************
void manageTrafficSimulation(int nbrOfStopSigns, int maximumCars, 
                             int maximumTraversalTime)
{


} // manageTrafficSimulation


// ****************************************************************
void *createCar(void *maxTraversalTimePtr)
{


} // End createCar
