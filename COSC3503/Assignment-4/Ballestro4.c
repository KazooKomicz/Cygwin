///////////////////////////////////////////////////////////////////
// Student name: Alyssa Ballestro
// Course: COSC 3503 - Operating Systems
// Assignment: #3 - Purposes of HTML Tags
// Source Code File name: Ballestro3
// Program's Purpose: Finds avg, sum, and max num of a table
// Program's Limitations: The report format is fixed to display results in a specific layout, limiting flexibility for different output styles.
// Development Computer: Lenovo Legion 5
// Operating System: Windows 11
// Compiler: Notepad++
// Program's Operational Status: In Progress
/////////////////////////////////////////////////////////////////// 

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_ROWS 7
#define MIN_ROWS 1
#define MAX_COLS 10
#define MIN_COLS 2
#define MAX_VAL 99

int readSize(FILE *file, int *rows, int *cols);
void processTable(FILE *file, int rows, int cols);
void printHeader(void);
void readRow(FILE *file, int count, int row[]);
void printRow(int rowNum, int count, int row[]);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: a.out <text_file_name>\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open the file\n");
        return EXIT_FAILURE;
    }

    int rows, cols;
    if (!readSize(file, &rows, &cols)) {
        fprintf(stderr, "Error: Row and/or column values are out of range\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    processTable(file, rows, cols);
    fclose(file);

    return EXIT_SUCCESS;
}

int readSize(FILE *file, int *rows, int *cols) {
    int r, c;
    if (fscanf(file, "%d %d", &r, &c) != 2) return FALSE;
    if (r < MIN_ROWS || r > MAX_ROWS || c < MIN_COLS || c > MAX_COLS) return FALSE;

    *rows = r;
    *cols = c;
    return TRUE;
}

void processTable(FILE *file, int rows, int cols) {
    printHeader();
    int row[cols];
    for (int i = 1; i <= rows; i++) {
        readRow(file, cols, row);
        printRow(i, cols, row);
    }
}

void printHeader(void) {
    printf("Row  Sum  Avg  Max\n");
    printf("---  ---  ---  ---\n");
}

void readRow(FILE *file, int count, int row[]) {
    for (int i = 0; i < count; i++) {
        if (fscanf(file, "%d", &row[i]) != 1 || row[i] < 0 || row[i] > MAX_VAL) {
            fprintf(stderr, "Error: Table values must be non-negative and not exceed %d\n", MAX_VAL);
            exit(EXIT_FAILURE);
        }
    }
}

void printRow(int rowNum, int count, int row[]) {
    int sum = 0, max = row[0];
    for (int i = 0; i < count; i++) {
        sum += row[i];
        if (row[i] > max) max = row[i];
    }
    double avg = (double)sum / count;
    printf("%3d  %3d  %5.1f  %3d\n", rowNum, sum, avg, max);
}
