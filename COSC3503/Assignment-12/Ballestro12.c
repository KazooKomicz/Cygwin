///////////////////////////////////////////////////////////////////
// Student name: Alyssa Ballestro
// Course: COSC 3503
// Assignment: #12 - Files and Directories
// Source Code File Name: Ballestro12.c
// Program's Purpose: Lists status information for all entries in a directory 
// Program's Limitations: Linux
// Development Computer:  Lenovo Legion 5
// Operating System: Windows 11 Cygwin
// Compiler: Cygwin/Notepad++
// Build Instructions: Code C
// Program's Operational Status: In Progress
///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

// Function Prototypes
void scan(const char *dir_name);
void columnPrint(const char *type, int size, const char *access, const char *status, const char *name);
const char *get_file_type(mode_t mode);
void get_access(mode_t mode, char *perm_str);
void get_status_change(time_t mod_time, char *time_str);

// Main Function
int main(int argc, char *argv[]) {
    const char *dir_name = (argc > 1) ? argv[1] : "."; // Use specified directory or current directory

    // Print the header and separator
    printf("%-20s %-10s %-11s %-20s %-s\n", "Type", "Size", "Access", "Status changed", "Name");
    printf("%-20s %-10s %-11s %-20s %-s\n", "----", "----", "------", "--------------", "----");

    scan(dir_name);
    return 0;
}

// Scan Function
void scan(const char *dir_name) {
    DIR *dir = opendir(dir_name);
    if (!dir) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        struct stat file_stat;
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_name, entry->d_name);

        if (stat(full_path, &file_stat) == -1) {
            perror("Error reading file information");
            continue; // Skip this entry
        }

        char access[11];
        get_access(file_stat.st_mode, permissions);

        char time_str[30]; // To hold the full time string
        get_status_change(file_stat.st_ctime, time_str);

        columnPrint(get_file_type(file_stat.st_mode), file_stat.st_size, permissions, time_str, entry->d_name);
    }

    closedir(dir);
}

// Column Print
void columnPrint(const char *type, int size, const char *access, const char *status, const char *name) {
    printf("%-20s %-10d %-11s %-20s %-s\n", type, size, access, status, name);
}

// Get File Type
const char *get_file_type(mode_t mode) {
    if (S_ISBLK(mode)) return "Block special file";
    if (S_ISCHR(mode)) return "Character special";
    if (S_ISDIR(mode)) return "Directory";
    if (S_ISFIFO(mode)) return "Pipe or FIFO";
    if (S_ISLNK(mode)) return "Symbolic link";
    if (S_ISREG(mode)) return "Regular file";
    if (S_ISSOCK(mode)) return "Socket";
    return "Unknown type";
}

// Get Access
void get_access(mode_t mode, char *perm_str) {
    perm_str[0] = (mode & S_IRUSR) ? 'r' : '-';
    perm_str[1] = (mode & S_IWUSR) ? 'w' : '-';
    perm_str[2] = (mode & S_IXUSR) ? 'x' : '-';
    perm_str[3] = (mode & S_IRGRP) ? 'r' : '-';
    perm_str[4] = (mode & S_IWGRP) ? 'w' : '-';
    perm_str[5] = (mode & S_IXGRP) ? 'x' : '-';
    perm_str[6] = (mode & S_IROTH) ? 'r' : '-';
    perm_str[7] = (mode & S_IWOTH) ? 'w' : '-';
    perm_str[8] = (mode & S_IXOTH) ? 'x' : '-';
    perm_str[9] = '\0';
}

// Get Status Time
void get_status_change(time_t mod_time, char *time_str) {
    struct tm *time_info = localtime(&mod_time);
    strftime(time_str, 30, "%b %d %H:%M:%S", time_info); // Full time format (e.g., Apr 1 04:19:34)
}



