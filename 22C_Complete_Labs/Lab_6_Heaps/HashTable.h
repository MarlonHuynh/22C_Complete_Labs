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

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Currency.h"
#include "Dollar.h"
#include "HashTableItem.h"

class HashTable {
public:
    HashTableItem** items;
    int size;
    int count;
    int collision; 
    // Constructor
    HashTable(int inputSize);
    // Destructor
    ~HashTable();
    // Insert
    void insert(double doubleOfCurrency); 
    // Search 
    void search(double numToSearchFor); 
    // Print
    void printSize(); 
    void printCount(); 
    void printCollision(); 
    void printLoadFactor(); 
};

/*Constructor
    Pre: inputSize must be a positive integer.
    Post: Initializes a HashTable object with the specified size, sets count and collision to 0, and allocates memory for the array of HashTableItem pointers.
    Return: None
*/
HashTable::HashTable(int inputSize) {
    size = inputSize;
    count = 0;
    collision = 0; 
    items = new HashTableItem * [size]; // Allocates memoory for the array of points to HashTableItem
    // Initialize all pointers to nullptr
    for (int i = 0; i < size; ++i) {
        items[i] = nullptr;
    }
}

/* Destructor
    Pre: None.
    Post: Deallocates memory for each HashTableItem object and the array of HashTableItem pointers.
    Return: None
*/
HashTable::~HashTable() {
    for (int i = 0; i < size; ++i) {
        delete items[i]; // Free memory of each item
    }
    delete[] items; // Free memory of the array
}

/*
    To hash your currency objects into the hash table, use the pseudorandom hash scheme - (m*w +  n*f) % size - where size = 29, m = 2, n = 3, w = whole value, f = fractional value.
*/
 /* Function to insert a currency into the hash table
    Pre: doubleOfCurrency must be a valid double value representing currency.
    Post: Inserts a new Currency object into the hash table based on the hash key calculated using a pseudorandom hash scheme. Handles collisions using quadratic probing.
    Return: None
*/

void HashTable::insert(double doubleOfCurrency) {
/*
    Create a new Currency object using doubleOfCurrency.
    Calculate the hash key using a pseudorandom hash scheme.
    If the slot at the calculated key is empty:
     a. Insert the Currency object into the table at the calculated key.
     b. Increment the count of items.
    Else (collision detected):
        a. Increment the collision count.
        b. Use quadratic probing to find an empty slot for insertion:
            i. Iterate through the slots using quadratic increments.
            ii. If an empty slot is found:
                - Insert the Currency object.
                - Increment the count of items.
                - Exit the loop.
    End of function.
*/
    Currency* inputCurrency = new Dollar(doubleOfCurrency); // Create a new Dollar object

    int m = 2;
    int n = 3;
    int w = inputCurrency->getMoneyWhole();
    int f = inputCurrency->getMoneyFraction();
    int key = (m * w + n * f) % size; // Calculate the hash key

    // Check if the slot is empty before inserting
    if (items[key] == nullptr) { 
        std::cout << "Inserting " << inputCurrency->printNoSpacesString() << ": Key is " << key << "." << std::endl;
        items[key] = new HashTableItem(key, inputCurrency); // Insert into table
        count++; // Increment count of items
    }
    
    else { // Collision detected  
        collision += 1; // Increment number of collisions
        //std::cout << "Collision detected at key " << key << ". Incremented collision count to " << collision << std::endl;
        
        // Quadratic probing  
        bool inserted = false; 
        for (int i = 1; i < size && inserted == false; i++) { 
            key = (key + (i * i)) % size; // Increment quadratic index and wraps around to the first bucket if it overflows  
            if (items[key] == nullptr) { // Found an empty spot! 
                std::cout << "Inserting " << inputCurrency->printNoSpacesString() << ": Key is " << key << ". Quadratic probing occurred." << std::endl;
                items[key] = new HashTableItem(key, inputCurrency); // Insert into table
                count++; // Increment count of items
                inserted = true;  
            }
            else { // Collision detected
                collision += 1; 
                //std::cout << "Collision detected at key " << key << ". Incremented collision count to " << collision << std::endl;
            }
        }
    }
}

/*  Function to search for a currency in the hash table
    Pre: numToSearchFor must be a valid double value representing currency.
    Post: Searches for a Currency object in the hash table based on the hash key calculated using a pseudorandom hash scheme. Prints whether the currency is found or not.
    Return: None
*/
void HashTable::search(double numToSearchFor) {
    /*
    Create a new Currency object using numToSearchFor.
    Calculate the hash key using a pseudorandom hash scheme.
    If the slot at the calculated key is not empty and contains the desired Currency object:
        a. Print that the currency is found at the calculated key.
    Else (collision or currency not found):
        a. Use quadratic probing to search for the currency:
            i. Iterate through the slots using quadratic increments.
            ii. If a slot containing the desired Currency object is found:
                - Print that the currency is found at the calculated key.
                - Exit the loop.
    If the currency is not found after probing:
        a. Print that the currency is not found.
    End of function.
*/
    Currency* currencyToSearchFor = new Dollar(numToSearchFor); //Create a new Dollar object for searching

    int m = 2;
    int n = 3;
    int w = currencyToSearchFor->getMoneyWhole();
    int f = currencyToSearchFor->getMoneyFraction();
    int key = (m * w + n * f) % size; // Calculate the hash key

    bool found = false;
    // Check if the first slot is full and checks if the slot has the correct Currency
    if (items[key] != nullptr) {
        if (currencyToSearchFor->isEqual(*items[key]->getCurrency())) { // Checks if slot has the correct currency
            std::cout << "Found " << currencyToSearchFor->printNoSpacesString() << ": Key is " << key << "." << std::endl;
            found = true; 
        }
        else { // Quadratic Probing begins   
            for (int i = 1; i < size && found == false; i++) { 
                key = (key + (i * i)) % size; // Increment quadratic index and wraps around to the first bucket if it overflows  
                if (items[key] != nullptr && currencyToSearchFor->isEqual(*items[key]->getCurrency())) { // Found an full slot and the slot has the correct currency! 
                    found = true;
                    std::cout << "Found " << currencyToSearchFor->printNoSpacesString() << ": Key is " << key << ". Quadratic probing occurred." << std::endl; 
                } 
            }
        }
    } 

    // If after probing 29 times and have not found the currency
    if (found == false) {
        std::cout << "Invalid data. Searched entire tree for " << currencyToSearchFor->printNoSpacesString() << ". No key found. " << std::endl;
    } 
    std::cout << std::endl; 

    // Deallocate currencyToSearchFor
    delete currencyToSearchFor; 

}


/*  Function to print the size of the hash table
    Pre: None.
    Post: Prints the size of the hash table.
    Return: None
*/
void HashTable::printSize() {
    std::cout << "The size of the hash table is " << size << "." << std::endl; 
}

/*  Function to print the count of items in the hash table
    Pre: None.
    Post: Prints the number of items in the hash table.
    Return: None
*/
void HashTable::printCount() {
    std::cout << "The numbers of items in the hash table is " << count << "." << std::endl;
}

 /* Function to print the number of collisions in the hash table
    Pre: None.
    Post: Prints the number of collisions that occurred during insertion into the hash table.
    Return: None
*/
void HashTable::printCollision() {
    std::cout << "The numbers of collision(s) is " << collision << "." << std::endl;
} 

/*  Function to calculate and print the load factor of the hash table
    Pre: None.
    Post: Calculates and prints the load factor of the hash table.
    Return: None
*/
void HashTable::printLoadFactor() {
    float factor = float(count) / float(size); 
    std::cout << "The load factor is " << factor << "." << std::endl;
}

#endif // HASHTABLE_H