///////////////////////////////////////////////////////////////////
// Student name: Alyssa Ballestro
// Course: COSC 3503 - Operating Systems
// Assignment: #5 - Reading files
// Source Code File name: Ballestro3
// Program's Purpose: Finds file details
// Program's Limitations: MUST have exit handler for each output w/o closing
// Development Computer: Lenovo Legion 5
// Operating System: Windows 11
// Compiler: Notepad++
// Program's Operational Status: In Progress
/////////////////////////////////////////////////////////////////// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Display Usage Message
void display_use() {
    printf("\nUsage:\n");
    printf("\n a.out\n");
    printf("\n a.out <environment_variable_name>\n");
    printf("\n a.out -a\n");
    exit(1);
}

// Exit Display
void display_exit() {
    printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("Environment Variable Display Program (by Alyssa Ballestro)\n");
}

// Display ONE env variable
void display_env_var(const char *var_name) {
    char *value = getenv(var_name);
    if (value) {
        printf("%s : %s\n", var_name, value);
    } else {
        printf("%s is not an existing environment variable name\n", var_name);
    }
}

// Display ALL env variables
void display_all_env_var() {
    extern char **environ;
    char **env = environ;

    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}

// Main Function
int main(int argc, char *argv[]) {
    atexit(display_exit); // Correctly register exit handler

    if (argc == 1) {
        // No command-line arguments: prompt for a variable name
        printf("Enter the name of an environment variable: ");
        char var_name[256];
        if (scanf("%255s", var_name) == 1) {
            display_env_var(var_name);
        } else {
            fprintf(stderr, "Error reading input.\n");
        }
    } else if (argc == 2) {
        if (strcmp(argv[1], "-a") == 0) {
            // Display all environment variables
            display_all_env_var();
        } else {
            // Display specific environment variable
            display_env_var(argv[1]);
        }
    } else {
        // Invalid usage
        display_use();
    }

    return 0;
}
