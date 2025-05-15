///////////////////////////////////////////////////////////////////
// Student name: Alyssa Ballestro
// Course: COSC 3503 - Operating Systems
// Assignment: #3 - Purposes of HTML Tags
// Source Code File name: Ballestro3
// Program's Purpose: Finds and prints a list of the HTML tags found in
//                    a file and the purpose of certain tags
// Program's Limitations: Assumes that the input file is a
//                        properly-formatted HTML file
// Development Computer: Lenovo Legion 5
// Operating System: Windows 11
// Compiler: Notepad++
// Program's Operational Status: In Progress
/////////////////////////////////////////////////////////////////// 

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define TRUE  1
#define FALSE 0
#define LEFT_ANGLE_BRACKET '<'
#define RIGHT_ANGLE_BRACKET '>'
#define SPACE ' '
#define MAX_LENGTH 100

// Function Prototypes
int detectTags(void);
void displayPurpose(char *tag);

// #############################################################
int main(void)
{
    int tagCount;

    printf("\n*** START OF HTML TAGS ***\n\n");

    tagCount = detectTags();

    printf("\nTOTAL NUMBER OF HTML TAGS FOUND: %d \n", tagCount);

    return 0;
} // End main

// #############################################################
int detectTags(void)
{
    char identifier[MAX_LENGTH];
    int index = 0;
    int count = 0;
    char symbol;

    symbol = getchar();

    while (!feof(stdin)) // Check for the end of the file
    {
        // Detect start of an HTML tag
        if (symbol == LEFT_ANGLE_BRACKET)
        {
            index = 0;
            symbol = getchar();

            // While inside the tag boundary
            while (symbol != RIGHT_ANGLE_BRACKET && symbol != EOF)
            {
                assert(index < MAX_LENGTH);
                identifier[index++] = symbol;
                symbol = getchar();
            } // End while

            assert(index < MAX_LENGTH);
            identifier[index] = '\0'; // End the identifier string

            displayPurpose(identifier);

            count++;
        } // End if

        symbol = getchar();
    } // End while

    return count;
} // End detectTags

// #############################################################
void displayPurpose(char *tag)
{
    // Convert tag to uppercase
    for (int i = 0; tag[i]; i++)
    {
        tag[i] = toupper(tag[i]);
    }

    // Print tag with angle brackets and its purpose
    printf("<%-18s> : ", tag);

    if (strncmp(tag, "HTML", MAX_LENGTH) == 0)
        printf("START OF HTML DOCUMENT\n");
    else if (strncmp(tag, "HEAD", MAX_LENGTH) == 0)
        printf("HEADER SECTION\n");
    else if (strncmp(tag, "TITLE", MAX_LENGTH) == 0)
        printf("DOCUMENT TITLE\n");
    else if (strncmp(tag, "BODY", MAX_LENGTH) == 0)
        printf("BODY OF THE HTML DOCUMENT\n");
    else if (strncmp(tag, "P", MAX_LENGTH) == 0)
        printf("PARAGRAPH\n");
    else if (strncmp(tag, "DIV", MAX_LENGTH) == 0)
        printf("DIVISION OR SECTION\n");
    else if (strncmp(tag, "SPAN", MAX_LENGTH) == 0)
        printf("SPAN ELEMENT\n");
    else if (strncmp(tag, "H1", MAX_LENGTH) == 0)
        printf("HEADER LEVEL 1\n");
    else
        printf("UNKNOWN HTML TAG\n");
} // End displayPurpose
