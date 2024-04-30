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

#ifndef STACK_H
#define STACK_H
class Stack : public SinglyLinkedList {
public:
    // Constructor
    Stack() : SinglyLinkedList() {}
    // Create the stack
    void createStack() { createList(); }
    // Destructor
    ~Stack() {}
    // Destroy the queue (Optional for overloading purposes)
    void destroyStack() { destroyList(); }
    
    // Push a Currency object to the top of the stack
    void push(Currency* currency);
    // Pop and return the Currency object from the top of the stack
    Currency* pop();
    // Peek and return a copy of the Currency object at the top of the stack
    Currency* peek();
    // Print the contents of the stack
    void printStack();
    // Check if the stack is empty
    bool isStackEmpty();
    // Count the number of Currency objects in the stack
    int countStack();
};
/*
    Function that pushes a currency object to the top
    Pre:        currency - the Currency object to add
    Post:       The currency object is added to the top of the stack
    Return:     None
*/
void Stack::push(Currency* currency) {
    addCurrency(currency, 0);
    setCount(getCount() + 1); 
}
/*
    Pop and return the Currency object from the top of stack
    Pre:        None
    Post:       The Currency object is removed from the top of the stack
    Return:     A pointer to the removed Currency object
*/ 
Currency* Stack::pop() {
    if (isStackEmpty() == true) { 
        return nullptr; // Stack is empty
    }
    return removeCurrency(0);
}
/*
    Peek and return the Currency object from the top of stack
    Pre:        None
    Post:       None
    Return:     A pointer to the removed Currency object
*/ 
Currency* Stack::peek() {
    if (isStackEmpty() == true) { 
        return nullptr; // Stack is empty 
    }
    return getCurrency(0);
}
/*
    Print the contents of the stack
    Pre:        None
    Post:       None
    Return:     A string containing the contents of the stack from top to bottom
*/
void Stack::printStack() {
    return printList();
}
/*
    Check if the stack is empty
    Pre:        None
    Post:       None
    Return:     True or false to whether the stack is empty or not
*/ 
bool Stack::isStackEmpty() {
    return isListEmpty();
}
/*
    Count the number of Currency objects in the stack
    Pre:        None
    Post:       None
    Return:     Int of the count of Currency objects in the stack
*/ 
int Stack::countStack() {
    return countCurrency();
}
#endif // STACK_H