/*
Project Information
Project Name:       Lab 5 - Hash Maps
Class:              W24 CIS D022C Data Abstract & Structures 04Y Goel 32936, 34068
Professor:          Manish Goel
Contributors:       Betty Huynh, Jorge David Olivas-Galdamez
Date Due:           March 17th, 2024

Program Information
IDE Used:           Visual Studio 2022
Language:           C++
*/

#ifndef HASHTABLEITEM_H
#define HASHTABLEITEM_H

#include "Currency.h"
#include "Dollar.h"

class HashTableItem {
public:
    int key; 
    Currency* currency; 
    // Constructor
    HashTableItem(int inputKey, Currency* inputCurrency);
    // Destructor
    ~HashTableItem();
    // Getter function for key
    int getKey();
    // Getter function for currency pointer
    Currency* getCurrency();
    // Setter function for key
    void setKey(int newKeyPtr);
    // Setter function for currency pointer
    void setCurrency(Currency* newCurrencyPtr);
};
/*  Constructor definition
    Pre: inputKey is the key value for the HashTableItem, inputCurrency is a valid pointer to a Currency object
    Post: Creates a new HashTableItem with the specified key and currency pointer
    Return: none
*/
HashTableItem::HashTableItem(int inputKey, Currency* inputCurrency) {
    key = inputKey; 
    currency = inputCurrency; 
}
/*  Destructor definition
    Pre: None
    Post: Deallocates memory for the currency object and sets currency pointer to nullptr
    Return: none
*/
HashTableItem::~HashTableItem() {
    delete currency; // Deallocate memory for Currency object
    currency = nullptr; // Set currency pointer to null to avoid dangling pointer
}
/*  Getter function for key
    Pre: None
    Post: Returns the key of the HashTableItem
    Return: Integer representing the key value
*/
int HashTableItem::getKey(){
    return key; 
}
/*  Getter function for currency pointer
    Pre: None
    Post: Returns the currency pointer of the HashTableItem
    Return: Pointer to a Currency object
*/
Currency* HashTableItem::getCurrency() {
    return currency; 
}
/*  Setter function for key
    Pre: newKeyPtr is the new key value for the HashTableItem
    Post: Sets the key of the HashTableItem to the new value
    Return: None
*/
void HashTableItem::setKey(int newKeyPtr) {
    key = newKeyPtr; 
}
/*  Setter function for currency pointer
    Pre: newCurrencyPtr is a valid pointer to a Currency object
    Post: Sets the currency pointer of the HashTableItem to the new value
    Return: None
*/
void HashTableItem::setCurrency(Currency* newCurrencyPtr) {
    currency = newCurrencyPtr; 
}

#endif // HASHTABLEITEM_H