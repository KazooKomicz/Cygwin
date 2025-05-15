////////////////////////////////////////////////////////////////
// Student name: Instructor
// Course: COSC 3503
// Assignment: Demonstration
// Source Code File Name: sortDemo.c
// Program's Purpose: Demonstrates how to use a bubble sort to sort integers
//    in an array  
// Program's Limitations: The array handles up to MAX_ROWS 
// Development Computer: Dell 
// Operating System: Windows 7 running CYGWIN
// Compiler: Gnu gcc
// Program's Operational Status: Satisfies all of the requirements
////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <time.h>

#define MAX_ROWS 20

// Function prototypes
void sortRows(int table[], const int counter);

// ###################################
int main(void)
{
int myTable[MAX_ROWS];
int i;

srand(time(NULL));

for (i = 0; i < MAX_ROWS; i++)
   {
   myTable[i] = rand() % 100;
   } // End for

printf("\nBefore sort: \n");
for (i = 0; i < MAX_ROWS; i++)
   {
   printf("%2d ", myTable[i]);
   } // End for

sortRows(myTable, MAX_ROWS);

printf("\nAfter sort: \n");
for (i = 0; i < MAX_ROWS; i++)
   {
   printf("%2d ", myTable[i]);
   } // End for

return 0;
} // End main


// ###################################
void sortRows(int table[], const int counter)
{
int temp;
int i;
int j;

for (i = counter - 2; i >= 0; i--)
   {
   for (j = 0; j <= i; j++)
      {
      if (table[j] > table[j + 1])
         {
         temp = table[j + 1];
         table[j + 1] = table[j];
         table[j] = temp;
         } // End if
      } // End j

   } // End for

} // End sortRows
