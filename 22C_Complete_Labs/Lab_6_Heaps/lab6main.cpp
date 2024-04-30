/*
Project Information
Project Name:       Lab 6 - Heaps
Class:              W24 CIS D022C Data Abstract & Structures 04Y Goel 32936, 34068
Professor:          Manish Goel
Contributors:       Marlon Huynh
Date Due:           March 21st, 2024

Program Information
IDE Used:           Visual Studio 2022
Language:           C++
*/

/*

THIS IS AN OPTIONAL LAB WHICH SHOULD BE DONE and THERE IS ONLY ONE SUBMISSION DATE FOR THIS LAB.

THIS LAB HAS TO BE SUBMITTED INDIVIDUALLY, i.e. either each person works on their own code or if the team pair wants to work together, both have to submit the same code separately. No Group submission is allowed.

Follow all code styling and submission instructions as outlined for previous labs.

    Derive a MinHeap class from the BST class of your Lab 4 code.
    Define/Override only the Search/Insert/Delete methods in the new class.
    Write a new main for this lab which:
        Will only be a test program for the MinHeap.
        Declares and creates a MinHeap object as necessary.
        Declares and creates the Dollar objects as necessary.
        Inserts the 20 Dollar objects specified in Lab 4 in the same order.
        Performs all 4 traversals after the inserting the 10th and the last objects - in total there will be 8 outputs which should be clearly demarcated.
        No user input is necessary, no data validation is necessary.
    For submission - upload all class files from Lab 4 as necessary as well as your new MinHeap class and the main. Remember to also include adequate number of screenshots of the program execution.
    The Discussion forum will be monitored and responded to all week during the Finals. Office Hours will only be held on MTW. For clarifications, post your questions on the Discussion forum first.



Grading:

Since this is an extra credit lab designed to boost your overall lab score (programming labs + zybooks labs), this lab has been made optional and the following criteria will be applied:

    10 pts - EXE created from your code works from command line.
    30 pts - MinHeap ADT
    10 pts - Your main
    You can also earn an additional early submission extra credit of 30% extra if submitted by EOD Thursday, i.e. 72 hours ahead of the deadline.
    The early submission extra credits will only be applied if both these conditions are met;
        Your score on the lab without the extra credit is at least 40.
        Your cumulative score on the five past programming labs is less than 550 points.
        Thus, the first 50 points is a true extra credit but the additional early submission extra credit is only a make up for past lost points.



Score downgrading related to guidelines in Lab - General Submission Instructions and Code Styling Guidelines

*/
#include <iostream>
#include <sstream>
#include <string> 
#include <fstream>

#include "MinHeap.h"

#define _CRTDBG_MAP_ALLOC // To see memory leaks in Visual Studio 

using namespace std;
 
int main() {

    // Welcome message
    cout << "******************************************************";
    cout << "\n  Welcome to the Lab 6 - Heaps demonstration!";
    cout << "\n\nContributors: Marlon Huynh\nIDE Used: Visual Studio 2022\nLanguage: C++";
    cout << "\n******************************************************\n\n";

    // Create min heap
    MinHeap* mh = new MinHeap;
    
    // Populating tree
    mh->insert(57.12);
    mh->insert(23.44);
    mh->insert(87.43);
    mh->insert(68.99);
    mh->insert(111.22);
    mh->insert(44.55);
    mh->insert(77.77);
    mh->insert(18.36);
    mh->insert(543.21);
    mh->insert(20.21);
    
    // Print using all 4 traversal methods
    mh->traverseAllMethods();

    // Continue populating tree
    mh->insert(345.67);
    mh->insert(36.18);
    mh->insert(48.48);
    mh->insert(101.00);
    mh->insert(11.00);
    mh->insert(21.00);
    mh->insert(51.00);
    mh->insert(1.00);
    mh->insert(251.00);
    mh->insert(151.00); 
    
    // Print using all 4 traversal methods
    mh->traverseAllMethods(); 
    
 
    cout << "\n\n*******************************************\n\tMemory Checks\n*******************************************\n";
    
    delete mh; 

    // To see memory leaks in Visual Studio
#ifdef _MSC_VER
    printf(_CrtDumpMemoryLeaks() ? "Memory Leak using _CrtDumpMemoryLeaks\n" : "No Memory Leak using _CrtDumpMemoryLeaks\n");
#endif

    cout << "\nThanks for using the heaps demonstration program!\n";
    
    return 0;

}
