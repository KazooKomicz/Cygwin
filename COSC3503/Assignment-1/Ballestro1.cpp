///////////////////////////////////////////////////////////////////
// Student Name: Alyssa Ballestro
// Course: COSC 3503 - Operating Systems
// Assignment: #1 - Using a Command Shell
// Source Code File Name: Ballestro1
// Program's Purpose: Give the square of a number and a list of the two after
// Program's Limitations: None known
// Development Computer: Lenovo Legion 7
// Operating System: Windows 11
// Compiler: Gnu g++
// Program's Operational Status:  
/////////////////////////////////////////////////////////////////// 

#include <iostream>
#include <iomanip> // Include for setw()
using namespace std;

int main() {
    char choice; // Variable to store user choice for restarting
    do { // Start a loop that will repeat
        int i; // Declare the integer variable inside the loop

        // Prompt User
        cout << "Enter a starting integer between 1 and 20: " << endl;
        cin >> i;

        // Check if the input is in the valid range
        if (i < 1 || i > 20) {
            cout << "ERROR: Please enter a number between 1 and 20." << endl;
            continue; // Skip the rest of the loop and start again
        }
        else {
            // Print header
            cout << "BASE    SQUARED" << endl;

            // Output the numbers and their squares, formatted with setw()
            cout << setw(3) << i << setw(10) << i * i << endl;
            i++;
            cout << setw(3) << i << setw(10) << i * i << endl;
            i++;
            cout << setw(3) << i << setw(10) << i * i << endl;
        }

        // Ask the user if they want to run the program again
        cout << "Do you want to enter another starting integer? (y/n): ";
        cin >> choice; // Read user choice
    } while (choice == 'y' || choice == 'Y'); // Continue if the user inputs 'y' or 'Y'

    return 0; // Exit program successfully
}
// End main
