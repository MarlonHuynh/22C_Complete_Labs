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

#ifndef LINKNODE_H
#define LINKNODE_H

#include "Currency.h" 

class LinkNode {
private: 
    //Currency* data;
    //LinkNode* next_node;

public: 
    Currency* data;
    LinkNode* next_node;
    // Default constructor
    LinkNode(Currency* currency) { data = currency; next_node = nullptr; }
};

#endif // LINKNODE_H