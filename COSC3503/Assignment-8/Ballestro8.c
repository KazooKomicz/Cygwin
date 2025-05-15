///////////////////////////////////////////////////////////////////
// Student name: Alyssa Ballestro
// Course: COSC 3503 - Operating Systems
// Assignment: #8 - Parallel Search using Threads
// Source Code File Name: 
// Program's Purpose: Provides the definitions for the functions that search a word puzzle file
// Program's Limitations: See the limitation comments in the puzzleSearcher.h file
// Development Computer: Lenovo Legion 5
// Operating System: Windows 11
// Compiler: Notepad++
// Build Instructions: See the driver module
// Operational Status: In Progress
///////////////////////////////////////////////////////////////////

#include <pthread.h>  // When linking this file with the driver file, also put
                      // "-lpthread" on the command line so that the linker
                      // obtains the pthread function definitions from the
                      // pthreads library

#include "puzzleSearcher.h"

#define MAX_THREADS 8

#define HORIZONTALLY_RIGHT      "horizontally to the right" 
#define HORIZONTALLY_LEFT       "horizontally to the left"
#define VERTICALLY_UP           "vertically up"
#define VERTICALLY_DOWN         "vertically down"
#define DIAGONALLY_DOWN_RIGHT   "diagonally down to the right"
#define DIAGONALLY_DOWN_LEFT    "diagonally down to the left"
#define DIAGONALLY_UP_RIGHT     "diagonally up to the right"
#define DIAGONALLY_UP_LEFT      "diagonally up to the left"


// Global Variables visible in this file only
static char puzzle[MAX_ROWS][MAX_COLUMNS];  
static int nbrOfPuzzleRows;
static int nbrOfPuzzleColumns;

static wordSearchType wordList[MAX_WORDS];
static int nbrOfWordsInList;


// Functions used to set and get the global variables from outside
// of this file

// ###############################################################
void setPuzzleDimensions(int rows, int columns)
{
	nbrOfPuzzleRows = rows;
	nbrOfPuzzleColumns = columns;
} // End setPuzzleDimensions


// ###############################################################
void setPuzzleCell(int row, int column, char symbol)
{
	puzzle[row][column] = symbol;
} // End setPuzzleCell


// ###############################################################
void setNbrOfWordsInList(int wordCount)
{
	nbrOfWordsInList = wordCount;
} // End setnbrOfWordsInList


// ###############################################################
int getNbrOfWordsInList(void)
{
	return nbrOfWordsInList;
} // End getnbrOfWordsInList


// ###############################################################
void setWordInList(int row, wordSearchType wordRecord)  
{
	wordList[row] = wordRecord;
} // End setWordInList


// ###############################################################
wordSearchType getWordFromList(int row)  
{
	return wordList[row];
} // End getWordFromList


// ================== MAKE NO CODE CHANGES ABOVE THIS LINE ==================


// Function Prototypes visible in this file only
static void *searchHorizontallyRight(void *parameter);
static void *searchHorizontallyLeft(void *parameter);
static void *searchVerticallyDown(void *parameter);
static void *searchVerticallyUp(void *parameter);
//EXTRA CREDIT
static void *searchDiagonallyDownRight(void *parameter); 
//static void *searchDiagonallyUpLeft(void *parameter);
//static void *searchDiagonallyUpRight(void *parameter);
//static void *searchDiagonallyDownLeft(void *parameter);


// ********************************************************
void performSequentialSearch(void)
{
	searchHorizontallyRight(NULL);
	searchHorizontallyLeft(NULL);  
    searchVerticallyDown(NULL);
    searchVerticallyUp(NULL);      
	
} // End performSequentialSearch


// ********************************************************
void performParallelSearch(void) 
{ 
	pthread_t threads[4];

    // Create threads for each direction
    pthread_create(&threads[0], NULL, searchHorizontallyRight, NULL);
    pthread_create(&threads[1], NULL, searchHorizontallyLeft, NULL);
    pthread_create(&threads[2], NULL, searchVerticallyDown, NULL);
    pthread_create(&threads[3], NULL, searchVerticallyUp, NULL);

    // Wait for threads to finish
    for (int i = 0; i < 4; i++) 
    {
        pthread_join(threads[i], NULL);
    }
	
	pthread_t diagonalThreads[1];
	
	pthread_create(&diagonalThreads[0], NULL, searchDiagonallyDownRight, NULL);
	//pthread_create(&diagonalThreads[1], NULL, searchDiagonallyUpLeft, NULL);
	//pthread_create(&diagonalThreads[2], NULL, searchDiagonallyUpRight, NULL);
	//pthread_create(&diagonalThreads[3], NULL, searchDiagonallyDownLeft, NULL);

	for (int i = 0; i < 1; i++) {
		pthread_join(diagonalThreads[i], NULL);
	}
} // End performParallelSearch


// ****************************************************************
static void *searchHorizontallyRight(void *parameter) 
{
	int listIndex;
	int wordIndex;
	int wordFound; // Boolean variable
	int puzzleRow;
	int puzzleStartColumn;
	int puzzleLastColumn;
	char word[MAX_WORD_SIZE];
	int wordLength;

	for (puzzleRow = 0; puzzleRow < nbrOfPuzzleRows; puzzleRow++)
	   {
	   for (listIndex = 0; listIndex < nbrOfWordsInList; listIndex++)
		  {
		  if (wordList[listIndex].found)
			 continue; // Skip over this word if it is already found
	 
		  strncpy(word, wordList[listIndex].forward, MAX_WORD_SIZE);
		  wordLength = wordList[listIndex].length;
		  puzzleLastColumn = nbrOfPuzzleColumns - wordLength;

		  for (puzzleStartColumn = 0; puzzleStartColumn <= puzzleLastColumn; puzzleStartColumn++)
			 {
			 wordFound = TRUE; // Assume the word is found until proven otherwise
			 for (wordIndex = 0; wordIndex < wordLength; wordIndex++)
				{
				if (puzzle[puzzleRow][puzzleStartColumn + wordIndex] != word[wordIndex]) 
				   {
				   wordFound = FALSE;
				   break; // Quit searching for word starting at this column in the puzzle
				   } // End if
				} // for wordIndex
	 
			 if (wordFound)  
				 break;  // Word was found, so stop searching this line
			 } // End for puzzleStartColumn

		  if (wordFound)
			 {  
			 wordList[listIndex].found = TRUE;
			 wordList[listIndex].startRow = puzzleRow;
			 wordList[listIndex].startColumn = puzzleStartColumn;
			 strcpy(wordList[listIndex].direction, HORIZONTALLY_RIGHT);
			 } // End if 

		  } // End listIndex
		
	   } // End for puzzleRow

} // End searchHorizontallyRight
static void *searchHorizontallyLeft(void *parameter) 
{
    int listIndex;
    int wordIndex;
    int wordFound; // Boolean variable
    int puzzleRow;
    int puzzleStartColumn;
    char word[MAX_WORD_SIZE];
    int wordLength;

    for (puzzleRow = 0; puzzleRow < nbrOfPuzzleRows; puzzleRow++) 
    {
        for (listIndex = 0; listIndex < nbrOfWordsInList; listIndex++) 
        {
            if (wordList[listIndex].found)
                continue; // Skip if already found

            strncpy(word, wordList[listIndex].forward, MAX_WORD_SIZE);
            wordLength = wordList[listIndex].length;

            for (puzzleStartColumn = wordLength - 1; puzzleStartColumn < nbrOfPuzzleColumns; puzzleStartColumn++) 
            {
                wordFound = TRUE; // Assume word is found until proven otherwise
                for (wordIndex = 0; wordIndex < wordLength; wordIndex++) 
                {
                    if (puzzle[puzzleRow][puzzleStartColumn - wordIndex] != word[wordIndex]) 
                    {
                        wordFound = FALSE;
                        break; // Quit searching for word starting at this column
                    }
                }

                if (wordFound)
                    break; // Word was found, stop searching this line
            }

            if (wordFound) 
            { 
                wordList[listIndex].found = TRUE;
                wordList[listIndex].startRow = puzzleRow;
                wordList[listIndex].startColumn = puzzleStartColumn;
                strcpy(wordList[listIndex].direction, HORIZONTALLY_LEFT);
            }
        }
    }
} // End searchHorizontallyLeft
static void *searchVerticallyDown(void *parameter) 
{
    int listIndex;
    int wordIndex;
    int wordFound; // Boolean variable
    int puzzleColumn;
    int puzzleStartRow;
    char word[MAX_WORD_SIZE];
    int wordLength;

    for (puzzleColumn = 0; puzzleColumn < nbrOfPuzzleColumns; puzzleColumn++) 
    {
        for (listIndex = 0; listIndex < nbrOfWordsInList; listIndex++) 
        {
            if (wordList[listIndex].found)
                continue; // Skip if already found

            strncpy(word, wordList[listIndex].forward, MAX_WORD_SIZE);
            wordLength = wordList[listIndex].length;

            for (puzzleStartRow = 0; puzzleStartRow <= nbrOfPuzzleRows - wordLength; puzzleStartRow++) 
            {
                wordFound = TRUE; // Assume word is found until proven otherwise
                for (wordIndex = 0; wordIndex < wordLength; wordIndex++) 
                {
                    if (puzzle[puzzleStartRow + wordIndex][puzzleColumn] != word[wordIndex]) 
                    {
                        wordFound = FALSE;
                        break; // Quit searching for word starting at this position
                    }
                }

                if (wordFound)
                    break; // Word was found, stop searching this column
            }

            if (wordFound) 
            { 
                wordList[listIndex].found = TRUE;
                wordList[listIndex].startRow = puzzleStartRow;
                wordList[listIndex].startColumn = puzzleColumn;
                strcpy(wordList[listIndex].direction, VERTICALLY_DOWN);
            }
        }
    }
} // End searchVerticallyDown
static void *searchVerticallyUp(void *parameter) 
{
    int listIndex;
    int wordIndex;
    int wordFound; // Boolean variable
    int puzzleColumn;
    int puzzleStartRow;
    char word[MAX_WORD_SIZE];
    int wordLength;

    for (puzzleColumn = 0; puzzleColumn < nbrOfPuzzleColumns; puzzleColumn++) 
    {
        for (listIndex = 0; listIndex < nbrOfWordsInList; listIndex++) 
        {
            if (wordList[listIndex].found)
                continue; // Skip if already found

            strncpy(word, wordList[listIndex].forward, MAX_WORD_SIZE);
            wordLength = wordList[listIndex].length;

            for (puzzleStartRow = wordLength - 1; puzzleStartRow < nbrOfPuzzleRows; puzzleStartRow++) 
            {
                wordFound = TRUE; // Assume word is found until proven otherwise
                for (wordIndex = 0; wordIndex < wordLength; wordIndex++) 
                {
                    if (puzzle[puzzleStartRow - wordIndex][puzzleColumn] != word[wordIndex]) 
                    {
                        wordFound = FALSE;
                        break; // Quit searching for word starting at this position
                    }
                }

                if (wordFound)
                    break; // Word was found, stop searching this column
            }

            if (wordFound) 
            { 
                wordList[listIndex].found = TRUE;
                wordList[listIndex].startRow = puzzleStartRow;
                wordList[listIndex].startColumn = puzzleColumn;
                strcpy(wordList[listIndex].direction, VERTICALLY_UP);
            }
        }
    }
} // End searchVerticallyUp
static void *searchDiagonallyDownRight(void *parameter) 
{
    int listIndex;
    int wordIndex;
    int wordFound; // Boolean variable
    int puzzleStartRow;
    int puzzleStartColumn;
    char word[MAX_WORD_SIZE];
    int wordLength;

    for (listIndex = 0; listIndex < nbrOfWordsInList; listIndex++) 
    {
        if (wordList[listIndex].found)
            continue; // Skip if already found

        strncpy(word, wordList[listIndex].forward, MAX_WORD_SIZE);
        wordLength = wordList[listIndex].length;

        // Check each starting position in the puzzle
        for (puzzleStartRow = 0; puzzleStartRow <= nbrOfPuzzleRows - wordLength; puzzleStartRow++) 
        {
            for (puzzleStartColumn = 0; puzzleStartColumn <= nbrOfPuzzleColumns - wordLength; puzzleStartColumn++) 
            {
                wordFound = TRUE; // Assume the word is found until proven otherwise
                for (wordIndex = 0; wordIndex < wordLength; wordIndex++) 
                {
                    if (puzzle[puzzleStartRow + wordIndex][puzzleStartColumn + wordIndex] != word[wordIndex]) 
                    {
                        wordFound = FALSE;
                        break; // Quit searching for this word
                    }
                }

                if (wordFound) 
                {
                    wordList[listIndex].found = TRUE;
                    wordList[listIndex].startRow = puzzleStartRow;
                    wordList[listIndex].startColumn = puzzleStartColumn;
                    strcpy(wordList[listIndex].direction, DIAGONALLY_DOWN_RIGHT);
                    break; // Stop searching this word
                }
            }
            if (wordFound) break; // Stop checking rows if word is found
        }
    }
    return NULL;
} // End searchDiagonallyDownRight

