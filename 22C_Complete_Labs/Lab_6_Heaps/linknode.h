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

#ifndef LINKNODE_H
#define LINKNODE_H

#include "Currency.h" 

class LinkNode {
public: 
    Currency* data;
    LinkNode* next_node;
    // Normal constructor
    LinkNode(Currency* currency) { data = currency; next_node = nullptr; }
};

#endif // LINKNODE_H