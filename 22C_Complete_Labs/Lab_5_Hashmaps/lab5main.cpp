/*
Project Information
Project Name:       Lab 5 - Hash Maps
Class:              W24 CIS D022C Data Abstract & Structures 04Y Goel 32936, 34068
Professor:          Manish Goel
Contributors:       Marlon Huynh, Jorge David Olivas-Galdamez
Date Due:           March 17th, 2024

Program Information
IDE Used:           Visual Studio 2022
Language:           C++
*/

#include <iostream>
#include <sstream>
#include <string> 
#include <fstream>

#include "currency.h"
#include "dollar.h" 
#include "linknode.h"
#include "HashTable.h"
#include "HashTableItem.h"

#define _CRTDBG_MAP_ALLOC // To see memory leaks in Visual Studio 

using namespace std;
 
int main() {

    // Welcome message
    cout << "******************************************************";
    cout << "\n  Welcome to the Lab 5 - Hash Table demonstration!";
    cout << "\n\nContributors: Marlon Huynh, Jorge David Olivas-Galdamez\nIDE Used: Visual Studio 2022\nLanguage: C++";
    cout << "\n******************************************************\n\n";

    // Create hashmap
    HashTable* ht = new HashTable(29); // Hashtable of size 29

    // Populating tree
    ht->insert(57.12);
    ht->insert(23.44);
    ht->insert(87.43);
    ht->insert(68.99);
    ht->insert(111.22);
    ht->insert(44.55);
    ht->insert(77.77);
    ht->insert(18.36);
    ht->insert(543.21);
    ht->insert(20.21);
    ht->insert(345.67);
    ht->insert(36.18);
    ht->insert(48.48);
    ht->insert(101.00);
    ht->insert(11.00);
    ht->insert(21.00);
    ht->insert(51.00);
    ht->insert(1.00);
    ht->insert(251.00);
    ht->insert(151.00);
    cout << endl;

    // Print number of items in tree
    ht->printCount();  
    // Print factor
    ht->printLoadFactor();  
    // Print number of collisions that occured
    ht->printCollision();  
    cout << endl; 

    // Interactivity 
    { // Limit the scope so Visual Studio's _CrtDumpMemoryLeaks memory detection doesn't detect a leak as it is called before the program ends
        string inp = "";
        double num = 0.0; 

        while (inp != "exit" && inp != "quit") { 
            cout << "Type: 'search [number]'    to search object in tree" << endl; 
            cout << "Type: 'exit' or 'quit'     to exit program" << endl;
            cout << "Enter: " << endl;
            cin >> inp;
            if (inp == "search") {
                cin >> num; 
                ht->search(num); 
            }
            else if (inp != "exit" && inp != "quit"){
                cout << "Invalid input. Please try again." << endl; 
            }

        }
    }
 
    cout << "\n\n*******************************************\n\tMemory Checks\n*******************************************\n";
    
    delete ht; 

    // To see memory leaks in Visual Studio
#ifdef _MSC_VER
    printf(_CrtDumpMemoryLeaks() ? "Memory Leak using _CrtDumpMemoryLeaks\n" : "No Memory Leak using _CrtDumpMemoryLeaks\n");
#endif

    cout << "\nThanks for using the hash table demonstration program!\n";
    
    return 0;

}
