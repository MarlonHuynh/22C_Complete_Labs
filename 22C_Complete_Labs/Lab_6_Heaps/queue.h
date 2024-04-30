/*
Project Information
Project Name:       Lab 6 - Heaps
Class:              W24 CIS D022C Data Abstract & Structures 04Y Goel 32936, 34068
Professor:          Manish Goel
Contributors:       Betty Huynh
Date Due:           March 21st, 2024

Program Information
IDE Used:           Visual Studio 2022
Language:           C++
*/

#ifndef QUEUE_H
#define QUEUE_H
 
#include "singlylinkedlist.h"

class Queue : public SinglyLinkedList {

public:
    // Constructor
    Queue() : SinglyLinkedList() {}
    // Create the queue (Optional for overloading purposes)
    void createQueue() { createList(); }
    // Destructor
    ~Queue() {}
    // Destroy the queue (Optional for overloading purposes)
    void destroyQueue() { destroyList(); }
    // Enqueue a Currency object to the end of the queue
    void enqueue(Currency* currency);
    // Dequeue and return the Currency object from the front of the queue
    Currency* dequeue();
    // Peek and return a copy of the Currency object at the front of the queue
    Currency* peekFront();
    // Peek and return a copy of the Currency object at the end of the queue
    Currency* peekRear();
    // Print the contents of the queue from front to end
    void printQueue();
    // Check if the queue is empty
    bool isQueueEmpty();
    // Count the number of Currency objects in the queue
    int countQueue();
};
/*
    Function that adds a Currency object to the end 
    Pre:        currency - the Currency object to add
    Post:       The currency object is added to the end of the queue
    Return:     None
*/ 
void Queue::enqueue(Currency* currency) { 
    addCurrency(currency, getCount()); 
}
/*
    Dequeue and return the Currency object from the front of the queue
    Pre:        None
    Post:       The Currency object is removed from the front of the queue
    Return:     A pointer to the removed Currency object
*/
Currency* Queue::dequeue() {
    if (isQueueEmpty()) {
        return nullptr; // Queue is empty
    }
    return removeCurrency(0);
}
/*
    Peek and return a copy of the Currency object at the front of the queue
    Pre:        None
    Post:       None
    Return:     A copy of the Currency object at the front of the queue
*/ 
Currency* Queue::peekFront() {
    if (isQueueEmpty()) {
        return nullptr; // Queue is empty
    }
    return getCurrency(0);
}
/*
    Peek and return a copy of the Currency object at the end of the queue
    Pre:        None
    Post:       None
    Return:     A copy of the Currency object at the end of the queue
*/ 
Currency* Queue::peekRear() {
    if (isQueueEmpty()) {
        return nullptr; // Queue is empty
    }
    return getCurrency(getCount() - 1);
}
/*
    Print the contents of the queue
    Pre:        None
    Post:       None
    Return:     A string containing the contents of the queue from front to end
*/
void Queue::printQueue() { return printList(); }
/*
    Check if the queue is empty
    Pre:        None
    Post:       None
    Return:     True if the queue is empty, False otherwise
*/
bool Queue::isQueueEmpty() { return isListEmpty(); }
/*
    Count the number of Currency objects in the queue
    Pre:        None
    Post:       None
    Return:     The number of Currency objects in the queue
*/
int Queue::countQueue() { return countCurrency(); }

#endif // QUEUE_H