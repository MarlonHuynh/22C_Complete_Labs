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

#include <iostream>
#include <sstream>
#include <string> 
#include "currency.h"
#include "dollar.h" 
#include "linknode.h"
#include "singlylinkedlist.h"
#include "queue.h"
#include "stack.h"

#define _CRTDBG_MAP_ALLOC // To see memory leaks in Visual Studio 

using namespace std;
 
int main() {

    // Welcome message
    std::cout << endl << "Welcome to the ADTs demonstration!" <<endl << endl;

    // Create 20 Dollar objects
    Currency* carr[20];
    carr[0] = new Dollar(57.12, "Dollar");
    carr[1] = new Dollar(23.44, "Dollar");
    carr[2] = new Dollar(87.43, "Dollar");
    carr[3] = new Dollar(68.99, "Dollar");
    carr[4] = new Dollar(111.22, "Dollar");
    carr[5] = new Dollar(44.55, "Dollar");
    carr[6] = new Dollar(77.77, "Dollar");
    carr[7] = new Dollar(18.36, "Dollar");
    carr[8] = new Dollar(543.21, "Dollar");
    carr[9] = new Dollar(20.21, "Dollar");
    carr[10] = new Dollar(345.67, "Dollar");
    carr[11] = new Dollar(36.18, "Dollar");
    carr[12] = new Dollar(48.48, "Dollar");
    carr[13] = new Dollar(101.00, "Dollar");
    carr[14] = new Dollar(11.00, "Dollar");
    carr[15] = new Dollar(21.00, "Dollar");
    carr[16] = new Dollar(51.00, "Dollar");
    carr[17] = new Dollar(1.00, "Dollar");
    carr[18] = new Dollar(251.00, "Dollar");
    carr[19] = new Dollar(151.00, "Dollar");

    // Create instances of SinglyLinkedList, Stack, and Queue
    SinglyLinkedList l;
    Stack s;
    Queue q;

    // Linked List operations

    cout << "----Initializing Linked List----" << endl << endl;
    cout << "Performing linked list operations" << endl; 
    cout << "Adding currency from 1 - 7 in reserse order..." << endl <<endl; 
    for (int i = 0; i < 7; i++) { 
        l.addCurrency(carr[6 - i], i);
    } 
    
    cout << "Searching and printing for Dollar object with value of 87.43 and 44.56..." << endl << endl;
    cout << "87.43 is located at index: " << l.findCurrency(new Dollar(87.43, "Dollar")) << endl;
    cout << "44.56 is located at index : " << l.findCurrency(new Dollar(44.56, "Dollar")) << endl << endl; 

    cout << "Removing Dollar object with value of 111.22..." << "\n";
    l.removeCurrency(new Dollar(111.22, "Dollar"));
    cout << "Removing Dollar object at index 2..." << endl << endl;
    l.removeCurrency(2);
    
    cout << "Printing list..." << endl << endl;

    l.printList();
    
    cout << endl; 

    cout << endl << "----Initializing Singly-Linked List----" << endl << endl;
    cout << "Adding 9th to 12th currency such as their index in singly-linked list is i % 5..." << endl;
    for (int i = 8; i < 11; ++i) {
        l.addCurrency(carr[i], i % 5);
    }

    cout << "Removing currencies at index count % 6 and count / 7..." << endl << endl;
    l.removeCurrency(l.getCount() % 6);
    l.removeCurrency(l.getCount() / 7);

    cout << "Printing list..." << endl << endl;
    l.printList();
    cout << endl; 
    
    // Stack operations

    for (int i = 12; i < 19; ++i)
        l.addCurrency(carr[i], i % 5);

    s.peek();
    s.pop();
    s.pop();
    s.pop();

    cout << endl << "----Initializing Stack----" << endl << endl;

    cout << "Adding 13th to 20th currency such as their index in the stack list" << endl << endl;
    cout << "Printing list..." << endl << endl;
    l.printList();
    cout << endl; 

    for (int i = 0; i < 7; ++i)
        l.addCurrency(carr [13 + i], i);

    cout << "Popping 2 objects..." << "\n";
    s.pop();
    s.pop();

    cout << endl << "Popping some currencies from the stack list" << endl << endl;
    cout << "Printing list..." << endl << endl;
    l.printList();
    cout << endl; 

    // Queue operations
    for (int i = 4; i < 12; i += 2)
        l.addCurrency(carr [i], i);

   q.peekFront();
   q.peekRear();
    
    q.dequeue();
    q.dequeue();

    cout << endl << "----Initializing Queue----" << endl << endl;

    cout << "Printing list..." << endl << endl;
    l.printList();
    cout << endl; 

    for (int i = 10; i < 15; ++i)
        l.addCurrency(carr [i], i);

    q.dequeue();
    q.dequeue();
    q.dequeue();

    cout << endl << "Printing final list..." << endl << endl;
    l.printList();
    cout << endl; 

    // Leaving message
    std::cout << endl << "Thanks for using the ADTs demonstration program!" << endl;

    // Clean up memory
    for (int i = 0; i < 20; ++i)
        delete carr[i];

    std::cout << "Memory cleared!" << endl << endl;

    return 0;
}