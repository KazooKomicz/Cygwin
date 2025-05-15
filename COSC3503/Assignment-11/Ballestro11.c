///////////////////////////////////////////////////////////////////
// Student name: ALyssa Ballestro
// Course: COSC 3503
// Assignment: #11 - Traffic Simulation
// Source Code File name: 
// Program's Purpose: Uses a semaphore and threads
//    to simulate traffic synchronization at an n-way stop intersection                 
// Program's Limitations: None known
// Development Computer: Lenovo Legion 5
// Operating System: Windows 11
// Compiler: Cygwin 11
// Build Instructions: complete partial code
// Program's Operation Status: In Progress
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
void manageTrafficSimulation(int nbrOfStopSigns, int maximumCars, int maximumTraversalTime) {
    // Declare variables
    pthread_t threads[nbrOfStopSigns];
    int status;
    int i;

    printf("=== TRAFFIC SIMULATION ===\n");
    printf("Simulation started with %d stop signs, max cars: %d, max traversal time: %d seconds.\n", 
           nbrOfStopSigns, maximumCars, maximumTraversalTime);

    srand(time(NULL));

    // Initialize semaphore with value 1 (binary semaphore)
    sem_init(&semaphore, 0, 1);

    for (i = 0; i < nbrOfStopSigns; i++) {
        if (pthread_create(&threads[i], NULL, createCar, &maximumTraversalTime) != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }

    // Wait until the maximum number of cars have completed traversing
    while (carCompletionCounter < maximumCars);

    // Cancel/Stop each thread
    for (i = 0; i < nbrOfStopSigns; i++) {
        pthread_cancel(threads[i]);
    }
    printf("Terminated all of the car creation threads.\n");

    // Join each thread
    for (i = 0; i < nbrOfStopSigns; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the end of simulation message
    printf("*** END OF TRAFFIC SIMULATION ***\n");

    // Destroy the semaphore
    sem_destroy(&semaphore);
} // manageTrafficSimulation


// ****************************************************************
void *createCar(void *maxTraversalTimePtr) {
    // Declare variables
    int carID, maxTraversalTime, traversalTime, nbrOfWaitingCars;

    // Dereference maxTraversalTimePtr to set maxTraversalTime
    maxTraversalTime = *(int *)maxTraversalTimePtr;

    while (1) {
        traversalTime = rand() % maxTraversalTime + 1;

        sleep(traversalTime);
        carCreationCounter++;

        // Assign car ID and calculate waiting cars
        carID = carCreationCounter;
        nbrOfWaitingCars = carCreationCounter - carCompletionCounter - 1;

        printf("Car %d arrived at the stop sign. Waiting cars: %d\n", carID, nbrOfWaitingCars);

        // Critical Section
        sem_wait(&semaphore);
        printf("Car %d is going through the intersection.\n", carID);

        sleep(traversalTime);

        sem_post(&semaphore);
        printf("Car %d has traversed the intersection.\n", carID);

        carCompletionCounter++;
    }
    return NULL;
}
