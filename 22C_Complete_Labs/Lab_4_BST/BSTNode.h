/*
Project Information
Project Name:       Lab 3 - Lists, Stacks and Queues
Class:              W24 CIS D022C Data Abstract & Structures 04Y Goel 32936, 34068
Professor:          Manish Goel
Contributors:       Marlon Huynh, Jorge David Olivas-Galdamez
Date Due:           Feb 17th, 2024

Program Information
IDE Used:           Visual Studio 2022
Language:           C++
*/

#ifndef BSTNODE_H
#define BSTNODE_H

#include "Currency.h"
#include "Dollar.h"


class BSTNode {
private:
    Currency* data;
    BSTNode* leftChild;
    BSTNode* rightChild;
public:
    // Default constructor
    BSTNode(); 
    // Constructor with input for root
    BSTNode(Currency* newData); 
    // Destructor
    ~BSTNode(); 
    // Getters
    Currency* getData() const;
    BSTNode* getLeftChild() const;
    BSTNode* getRightChild() const;
    // Setters
    void setData(Currency* newData); 
    void setLeftChild(BSTNode* newLeftChild);
    void setRightChild(BSTNode* newRightChild);
};
/*
    Constructors of the binary tree node
    Pre:    None or a BSTNode newRoot
    Post:   Assigns data to nullptr/BSTNode newData
    Return: None
*/
BSTNode::BSTNode() {
    data = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;
}
BSTNode::BSTNode(Currency* newData) {
    data = newData;
    leftChild = nullptr;
    rightChild = nullptr;
}
/*
    Destructor of the binary tree node
    Pre:    None 
    Post:   Deletes data
    Return: None
*/
BSTNode::~BSTNode() {
    delete data;
}
/*
    Getters
    Pre:    None
    Post:   None
    Return: data, leftChild, or rightChild respectively
*/
Currency* BSTNode::getData() const { return data; }
BSTNode* BSTNode::getLeftChild() const { return leftChild; }
BSTNode* BSTNode::getRightChild() const { return rightChild; }
/*
    Setters
    Pre:    a new Currency* for data, BSTNode* for leftChild, or BSTNode* for rightchild respectively
    Post:   Changes the data, leftChild, or rightChild to the new data
    Return: None
*/
void BSTNode::setData(Currency* newData) {
    data = newData;
}
void BSTNode::setLeftChild(BSTNode* newLeftChild) {
    leftChild = newLeftChild; 
}
void BSTNode::setRightChild(BSTNode* newRightChild) {
    rightChild = newRightChild; 
}

#endif // BSTNODE_H
