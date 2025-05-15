///////////////////////////////////////////////////////////////////
// Student name: Instructor
// Course: COSC 3503
// Assignment: #8 - Parallel Searching using Threads
// File name: program8-driver.c
// Program's Purpose: Provides the main function which calls the functions that read in  
//    and search a word puzzle
// Program's Assumptions: The format of the word puzzle file consists of two integers on the
//    first line representing the number of rows and columns.  This line
//    is followed by rows of upper-case characters representing the word
//    puzzle.  The characters start at the beginning of the line and are
//    separated from each other by one blank space.  The format of the
//    word list file consists of one integer on the first line representing
//    the number of words in the file, followed by one word per line.  The 
//    words contain all upper-case letters and contain no blank spaces.
//    For example, "Hall stand" appears as "HALLSTAND".
// Program's Limitations: See limitation comments in puzzleSearcher.h file.  Maximum name of
//    any puzzle file is MAX_NAME_SIZE
// Development Computer: Dell 
// Operating System: Windows XP using CYGWIN
// Compiler: Gnu gcc
// Build Instructions: gcc program8-driver.c student8.c
// Program's Operation Status: All requirements have been met
///////////////////////////////////////////////////////////////////

#include "puzzleSearcher.h"

#define MAX_NAME_SIZE 50
#define MAX_BUFFER_SIZE 200


// Function Prototypes
void parseCommandLine(int argumentCount, char *arguments[], 
                      int *parallelSearchFlagPtr, 
                      char *puzzleName, char *wordListName);
void readPuzzleFile(FILE *fileID);
int readWordListFile(FILE *fileID);
void displayLocationsOfWords(int longestWordLength);


// ********************************************************
int main(int argc, char* argv[])
{
	char puzzleFileName[MAX_NAME_SIZE];
	char wordListFileName[MAX_NAME_SIZE];
	int parallelSearchDesired;
	FILE *puzzleFileID;
	FILE *wordListFileID;
	int longestWordLength;

	parseCommandLine(argc, argv, &parallelSearchDesired, puzzleFileName, wordListFileName);

	puzzleFileID = fopen(puzzleFileName, "r"); 
	if (puzzleFileID  == 0)
	   {
		perror("\nProblem opening puzzle file");
		exit(1);
	   } // End if

	wordListFileID = fopen(wordListFileName, "r"); 
	if (wordListFileID == 0)
	   {
		perror("\nProblem opening word list file");
		exit(1);
	   } // End if

	readPuzzleFile(puzzleFileID);

	longestWordLength = readWordListFile(wordListFileID);

	if (parallelSearchDesired)
	   performParallelSearch();
	else
	   performSequentialSearch();

	displayLocationsOfWords(longestWordLength);

	return 0;
} // End main



// ********************************************************
void parseCommandLine(int argumentCount, char *arguments[], int *parallelSearchFlagPtr, char *puzzleName, char *wordListName)
{
	if (argumentCount != 4)
	   {
		   fprintf(stderr, 
				   "\nUsage: a.out search_type puzzle_file_name word_list_file_name\n\n");
		   fprintf(stderr, "search_type : -s for sequential search\n");
		   fprintf(stderr, "              -p for parallel search\n\n");
		   fprintf(stderr, "Minimum puzzle size: %d rows and %d columns\n", 
				   MIN_ROWS, MIN_COLUMNS);
		   fprintf(stderr, "Maximum puzzle size: %d rows and %d columns\n", 
				   MAX_ROWS, MAX_COLUMNS);
		   fprintf(stderr, "Maximum number of words: %d\n", MAX_WORDS);
		   fprintf(stderr, "Maximum word size: %d\n", MAX_WORD_SIZE);
		   exit(1);
	   } // End if

	if (strcmp(arguments[1],"-p") == 0)
	   *parallelSearchFlagPtr = TRUE;
	else if (strcmp(arguments[1],"-s") == 0)
	   *parallelSearchFlagPtr = FALSE;
	else
	   {
		   fprintf(stderr, "\nUnknown search type.  Use -s or -p\n");
		   exit(1);
	   } // End else   

	strncpy(puzzleName, arguments[2], MAX_NAME_SIZE);
	strncpy(wordListName, arguments[3], MAX_NAME_SIZE);

} // End parseCommandLine


// ********************************************************
void readPuzzleFile(FILE *fileID)
{
	char buffer[MAX_BUFFER_SIZE];
	int nbrOfRows;
	int nbrOfColumns;
	int row;
	int column;

	fgets(buffer, MAX_BUFFER_SIZE, fileID);
	sscanf(buffer, "%d %d", &nbrOfRows, &nbrOfColumns);

	setPuzzleDimensions(nbrOfRows, nbrOfColumns);

	for (row = 0; row < nbrOfRows; row++)
	   {
	   fgets(buffer, MAX_BUFFER_SIZE, fileID);

	   // Store puzzle characters
	   for (column = 0; column < nbrOfColumns; column++)
		  {
		  // OLD: puzzle[row][column] = buffer[column * 2];
		  setPuzzleCell(row, column, buffer[column * 2]);
		  } // End for

	   } // End for
} // End readPuzzleFile 


// ********************************************************
int readWordListFile(FILE *fileID)
{
	char buffer[MAX_BUFFER_SIZE];
	wordSearchType wordRecord;
	int nbrOfWords;
	int row;
	int index;
	int length;
	int longestWordLength = 0;  

	fgets(buffer, MAX_BUFFER_SIZE, fileID);
	sscanf(buffer, "%d", &nbrOfWords);

	setNbrOfWordsInList(nbrOfWords);

	for (row = 0; row < nbrOfWords; row++)
	   {
	   fgets(buffer, MAX_BUFFER_SIZE, fileID);  // Read the whole line
	   sscanf(buffer, "%s", wordRecord.forward); // Read first word on the line
	   wordRecord.length = strlen(wordRecord.forward);
	   length = wordRecord.length;
	   if (wordRecord.length > longestWordLength)
		  longestWordLength = wordRecord.length;  

	   // Store a reversed version of the word to help out in the actual word search
	   for (index = 0; index < wordRecord.length; index++)
		  {
		  wordRecord.backward[length - index - 1] = wordRecord.forward[index];
		  } // End for
	   wordRecord.found = FALSE;
	   setWordInList(row, wordRecord);  

	   } // End for

	return longestWordLength;

} // End readWordListFile


// ********************************************************
void displayLocationsOfWords(int longestWordLength)
{
	int i;
	int nbrOfWords;
	wordSearchType wordRecord;

	nbrOfWords = getNbrOfWordsInList();

	printf("\n*** LOCATIONS OF WORDS ***\n\n");
	for (i = 0; i < nbrOfWords; i++)
	   {
	   wordRecord = getWordFromList(i);
	   printf("%-*s : ", longestWordLength, wordRecord.forward); 
	   if (wordRecord.found)
		  printf("starts at (%d,%d) and extends %s\n", wordRecord.startRow + 1,
				  wordRecord.startColumn + 1, wordRecord.direction);
	   else
		  printf("was not found\n");
		  
	   } // End for

} // End displayLocationsOfWords

