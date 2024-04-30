/*
Project Information
Project Name:       Lab 3 - Lists, Stacks and Queues
Class:              W24 CIS D022C Data Abstract & Structures 04Y Goel 32936, 34068
Professor:          Manish Goel
Contributors:       Betty Huynh, Jorge David Olivas-Galdamez 
Date Due:           Feb 7th, 2024

Program Information
IDE Used:           Visual Studio 2022
Language:           C++
*/

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include "linknode.h"
#include "currency.h"

class SinglyLinkedList {
private:
    int count;
    LinkNode* head;
    LinkNode* tail;

public:
    // Constructor
    SinglyLinkedList() { count = 0; head = nullptr; tail = nullptr; }
    // Create list (Optional for overloading purposes)
    void createList() { count = 0; head = nullptr; tail = nullptr; }
    // Destructor
    ~SinglyLinkedList() { destroyList(); };
    // Destroy list (Optional for overloading purposes)
    void destroyList();
    // Getters 
    int getCount() const;
    LinkNode* getHead() const;
    LinkNode* getTail() const;
    // Setters
    void setCount(int newCount);
    void setHead(LinkNode* newHead);
    void setTail(LinkNode* newTail);
    // Add a Currency object at the specified index
    void addCurrency(Currency* currency, int index);
    // Remove a Currency object from the list
    Currency* removeCurrency(Currency* currency);
    // Overloaded method remove a Currency object from the list at the specified index
    Currency* removeCurrency(int index);
    // Find the index of a Currency object in the list
    int findCurrency(Currency* currency);
    // Get the Currency object at the specified index
    Currency* getCurrency(int index);
    // Print the contents of the list
    void printList();
    // Check if the list is empty
    bool isListEmpty();
    void addCount(); 
    // Count the number of Currency objects in the list
    int countCurrency();
};
/*
    Function to destroy the list
    Pre:        None
    Post:       Destroys the list
    Return:     None
*/
void SinglyLinkedList::destroyList() {
    LinkNode* current = head;
    while (current != nullptr) {
        LinkNode* next = current->next_node;
        delete current;
        current = next;
    }
    count = 0;
    head = nullptr;
    tail = nullptr;
}
/*
    Getters for the count, head, and tail
    Pre:        None
    Post:       None
    Return:     The count int, head Currency*, or tail Currency*, respectively
*/
int SinglyLinkedList::getCount() const { return count; }
LinkNode* SinglyLinkedList::getHead() const { return head; }
LinkNode* SinglyLinkedList::getTail() const { return tail; }
/*
    Setters for the count, head, and tail
    Pre:        newCount, newHead, newTail - the int and objects to change to, respectively
    Post:       Count, head, and tail gets motified, respectively
    Return:     None
*/
void SinglyLinkedList::setCount(int newCount) { count = newCount; }
void SinglyLinkedList::setHead(LinkNode* newHead) { head = newHead; }
void SinglyLinkedList::setTail(LinkNode* newTail) { tail = newTail; } 
/*
    Add a Currency object at the specified index
    Pre:        currency - the currency object to add
                index - the int index to add the object at
    Post:       The singly linked list is motified to have object currency at the index with updated pointers accordingly
    Return:     None
*/
void SinglyLinkedList::addCurrency(Currency* currency, int index) {
    if (index < 0 || index > count) { // Invalid index
        return;
    }
    LinkNode* new_node = new LinkNode(currency);
    if (index == 0) { // Insert at the beginning
        new_node->next_node = head;
        head = new_node;
        if (tail == nullptr) {
            tail = new_node;
        }
    }
    else if (index == count) { // Insert at the end 
        tail->next_node = new_node;
        tail = new_node;
    }
    else { // Insert in the middle 
        LinkNode* current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next_node;
        }
        new_node->next_node = current->next_node;
        current->next_node = new_node;
    }
    count++; // Updates the count of objects in the singly linked list 
} 
/*
    Remove a Currency object from the list
    Pre:        currency - the Currency object to remove
    Post:       The singly linked list gets the specified object removed
    Return:     Nothing
*/
Currency* SinglyLinkedList::removeCurrency(Currency* currency) {
    LinkNode* current = head;
    LinkNode* prev = nullptr;
    while (current != nullptr) {
        if (current->data->isEqual(*currency)) { // Find the Currency object 
            if (prev != nullptr) {
                prev->next_node = current->next_node; // If current is not the head, update the previous node
            }
            else {
                head = current->next_node; // If current is the head, update the head node
            }
            if (current == tail) { // If current is the tail, update the tail node
                tail = prev;
            }
            Currency* removedCurrency = current->data;
            delete current;
            count--; // Update the count of objects in singly linked list
            return removedCurrency;
        }
        // Move to the next node 
        prev = current;
        current = current->next_node;
    }
    return nullptr; // Currency object not found
}
/*
    Overloaded method to remove a Currency object from the list at the specified index
    Pre:        index - the index to remove Currency object at 
    Post:       The singly linked list has an object removed at index
    Return:     None
*/
Currency* SinglyLinkedList::removeCurrency(int index) {
    if (index < 0 || index >= count) { // Invalid index
        return nullptr;
    }
    LinkNode* current = head;
    LinkNode* prev = nullptr;
    for (int i = 0; i < index; ++i) { // go to the index 
        prev = current;
        current = current->next_node;
    }
    if (prev != nullptr) { 
        prev->next_node = current->next_node; // Update the next pointer of the previous node
    }
    else {
        head = current->next_node; // Update the head if the node to be removed is the first node
    }
    if (current == tail) { 
        tail = prev; // Update the tail if the node to be removed is the last node
    }
    Currency* removedCurrency = current->data;
    delete current;
    count--;
    return removedCurrency;
} 
/*
    Find the index of a Currency object in the list
    Pre:        currency - the Currency object to find
    Post:       None
    Return:     Returns the index of found object if found, else, returns -1
*/
int SinglyLinkedList::findCurrency(Currency* currency) {
    LinkNode* current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->data->isEqual(*currency)) {
            return index;
        }
        ++index;
        current = current->next_node;
    }
    return -1; // Currency not found
} 
/*
    Get the Currency object at the specified index
    Pre:        index - the index to find the Currency object at 
    Post:       None
    Return:     the specified Currency object's data
*/
Currency* SinglyLinkedList::getCurrency(int index) {
    if (index < 0 || index >= count) {
        return nullptr; // Invalid index
    }
    LinkNode* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next_node;
    }
    return current->data;
} 
/*
    Print the contents of the list
    Pre:        None
    Post:       Prints the content of the list 
    Return:     None
*/
void SinglyLinkedList::printList() { 
    LinkNode* current = head;
    while (current != nullptr) {
        current->data->print();
        current = current->next_node;
    } 
} 
/*
    Check if the list is empty
    Pre:        None
    Post:       None
    Return:     True or false whether the list is empty
*/
bool SinglyLinkedList::isListEmpty() {
    if (count == 0) { return true; }
    return false;
} 
/*
    Count the number of Currency objects in the list
    Pre:        None   
    Post:       None
    Return:     The count of the numbers of Currency objects in the singly linked list
*/
int SinglyLinkedList::countCurrency() {
    return count;
}

#endif // SINGLYLINKEDLIST_H
