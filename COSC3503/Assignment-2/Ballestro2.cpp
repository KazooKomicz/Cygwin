///////////////////////////////////////////////////////////////////
// Student Name:
// Course: COSC 3503 - Operating Systems
// Assignment: #2 - HTML Tag Detection
// Source Code File Name: Ballestro2.cpp
// Program's Purpose: Detects and prints HTML tags from a file
// Program's Limitations: None known
// Development Computer: Lenovo Legion 7
// Operating System: Windows 11
// Compiler: Gnu g++
// Program's Operational Status: In Dev
///////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

int main() {
    // Print start message
    cout << "*** START OF HTML TAGS ***" << endl << endl;

    char ch;
    bool inTag = false; // Flag to track if we're inside a tag
    int tagCount = 0;

    // Temporary storage for the current tag
    string curTag = "";

    // Read input character by character
    while (cin.get(ch)) {
        if (ch == '<') {
            // Start of a tag
            inTag = true;
            curTag += ch;
        } else if (ch == '>' && inTag) {
            // End of a tag
            curTag += ch;
            // Print the tag
            cout << curTag << endl;
            // Increment the tag count
            tagCount++;
            // Reset the tag and flag
            curTag = "";
            inTag = false;
        } else if (inTag) {
            // Characters inside the tag
            curTag += ch;
        }
    }

    // Print the tag count summary
    cout << endl;
    cout << "TOTAL NUMBER OF HTML TAGS FOUND: " << tagCount << endl;

    return 0;
}
