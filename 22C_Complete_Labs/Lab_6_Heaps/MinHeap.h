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

#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream> 
#include <fstream>
#include <queue>
#include <stack>

#include "Currency.h"
#include "Dollar.h"
#include "BST.h"
#include "BSTNode.h" 

class MinHeap : public BST {
public:
    // Search
    BSTNode* search(double cash);
    BSTNode* searchNoPrint(double cash);
    // Insert
    void insert(double cash);  
    void percolateDown(BSTNode* node);
    // Delete
    void deleteNode(double cash); 
    BSTNode* findLastNode(); 
    void percolateUp(BSTNode* node);  
};
/*
    Linear search level by level
    Pre:    cash - double of the cash value to search for
    Post:   Prints whether the node was found or not
    Return: BSTNode* of the node if matching value is found, otherwise, returns a nullptr
*/ 
BSTNode* MinHeap::search(double cash) { 
    /* PSEUDOCODE
        Set the current node to the root node
        Create a queue of BSTNode* 
        While the queue isn't empty
            Check if the current node has the currency to search for
                If yes, found node and return it 
            Pop the queue
            Add the left and right child to the queue if possible
        If after the while loop, there is node with the currency to search for
            return null pointer
    */
    Currency* dollarToSearchFor = new Dollar(cash);  
    std::queue<BSTNode*> bstnodeQueue; // Uses std::queue for BSTNode pointers 
    bstnodeQueue.push(root); 
    while (!bstnodeQueue.empty()) {
        // Check if the current BSTNOde has the Currency to search for
        BSTNode* current = bstnodeQueue.front();
        if (current->getData()->isEqual(*dollarToSearchFor)) { // Found
            std::cout << "Searching: Found " << dollarToSearchFor->printNoSpacesString() << std::endl;
            delete dollarToSearchFor;
            return current; 
        }
        bstnodeQueue.pop();  
        // Add the left child to the queue
        if (current->getLeftChild() != nullptr) { 
            bstnodeQueue.push(current->getLeftChild());
        } 
        // Add the right child to the queue
        if (current->getRightChild() != nullptr) {
            bstnodeQueue.push(current->getRightChild());
        }
    } 
    std::cout << "Searching: Didn't find " << dollarToSearchFor->printNoSpacesString() << std::endl;
    delete dollarToSearchFor; 
    return nullptr;
}
/*
    Linear search level by level without the print statements
    Pre:    cash - double of the cash value to search for
    Post:   Prints whether the node was found or not
    Return: BSTNode* of the node if matching value is found, otherwise, returns a nullptr
*/ 
BSTNode* MinHeap::searchNoPrint(double cash) { 
    /* PSEUDOCODE
        Same as search function's pseudocode
    */
    Currency* dollarToSearchFor = new Dollar(cash); 
    std::queue<BSTNode*> bstnodeQueue; // Uses std::queue for BSTNode pointers 
    bstnodeQueue.push(root); 
    while (!bstnodeQueue.empty()) {
        // Check if the current BSTNOde has the Currency to search for
        BSTNode* current = bstnodeQueue.front();
        if (current->getData()->isEqual(*dollarToSearchFor)) { // Found 
            delete dollarToSearchFor;
            return current;
        }
        bstnodeQueue.pop();
        // Add the left child to the queue
        if (current->getLeftChild() != nullptr) {
            bstnodeQueue.push(current->getLeftChild());
        }
        // Add the right child to the queue
        if (current->getRightChild() != nullptr) {
            bstnodeQueue.push(current->getRightChild());
        }
    } 
    delete dollarToSearchFor;
    return nullptr;
}
/*
    Function to insert a new node into the min heap of value cash
    Pre:    cash - double of the cash value to search for, assumes this is a valid double
    Post:   Inserts a new node of value cash into the min heap, preserving min heap properties
    Return: None
*/
void MinHeap::insert(double cash) {
    /* PSEUDOCODE
        Create a Dollar object with double cash
        Check if tree is empty
            If true insert as root and return
        Make a queue of BSTNodes 
        Push the root
        While the queue isn't empty:
            Pop the top of the queue (current node)
            Check if the current node has a left child
                If nullptr is child, found place to insert
                    After insertion, percolates upwards and return
                If has child, then push to queue
            Check if the current node has a right child
                If nullptr is child, found place to insert
                    After insertion, percolates upwards and return
                If has child, then push to queue

        **Effectively, this code traverses the tree level by level, adding the BSTNodes in the same level left to right into a queue, and dequeues until it finds the first null spot to insert at and percolate up at, maintaining the property that min heap trees must have the minimum number of levels possible  
    */ 
    BSTNode* bstNodeToInsert = new BSTNode(new Dollar(cash));
    printStatement_WithEndl("Inserting " + bstNodeToInsert->getData()->printNoSpacesString() + ": Node is successfully added");
    // If the tree is empty, insert at the root and return (insertion complete)
    if (root == nullptr) {
        root = bstNodeToInsert; 
        return;
    }
    std::queue<BSTNode*> bstnodeQueue; // Uses std::queue for BSTNode pointers
    bstnodeQueue.push(root);
    
    while (!bstnodeQueue.empty()) {
        BSTNode* current = bstnodeQueue.front();
        bstnodeQueue.pop(); 
        // Check if left child of the current node is null
        if (current->getLeftChild() == nullptr) {
            // Found place to insert
            current->setLeftChild(bstNodeToInsert);         // Sets left child with new node 
            current->getLeftChild()->setParent(current);    // Sets new node's parents 
            percolateUp(current->getLeftChild());           // Percolate upwards 
            return;                                         // Returns (insertion complete)
        }
        else {
            bstnodeQueue.push(current->getLeftChild()); // Add the left child to the queue
        } 
        // Check if right child of the current node is null
        if (current->getRightChild() == nullptr) {
            // Found place to insert
            current->setRightChild(bstNodeToInsert);        // Sets right child with new node 
            current->getRightChild()->setParent(current);   // Sets new node's parents 
            percolateUp(current->getRightChild());          // Percolate upwards  
            return;                                         // Returns (insertion complete)
        }
        else {
            bstnodeQueue.push(current->getRightChild());    // Add the right child to the queue
        }
    }
}
/*
    Percolate up function used to reorganize the tree after insertion, used in deleteNode
    Pre:    node - the node to percolate up at 
    Post:   The min heap's properties is presevered at the path where it percolates up at
    Return: None
*/
void MinHeap::percolateUp(BSTNode* node) {
    /*  PSEUDOCODE
        While the current node isnt the root and the current's dollar value is greater than the parent's dollar value
            Swap the dollar value of the current and the parent
            Move up to the parent
    */
    while (node != root && node->getParent()->getData()->isGreater(*node->getData())) {
        // Swap data between node and parent
        Currency* temp = node->getData();
        node->setData(node->getParent()->getData());
        node->getParent()->setData(temp);
        // Move to the parent for the next iteration
        node = node->getParent();
    }
}
/*
    Function to delete a node of value cash
    Pre:    cash - double of the cash value to delete
    Post:   Deletes a node of value cash if possible
    Return: None
*/
void MinHeap::deleteNode(double cash) { 
    /* PSEUDOCODE
        Search for the node to delete in min heap
        Get the last node of the min heap
        Change the data of the node to delete to be the same as the last node's data, making sure that they use different pointers
        Delete the last node's parent pointer to the node (either left child or right child)
        Delete the last node
        Percolate down at the node to delete location to fix min heap properties after deletion
    */
    // Find node to delete
    BSTNode* nodeToDelete = searchNoPrint(cash); 
    if (nodeToDelete == nullptr) {
        printStatement_WithEndl("Deleting " + std::to_string(cash) + " Dollar : Deleting node is unsuccessful. Node is not found.");
        return; 
    }
    printStatement_WithEndl("Deleting " + nodeToDelete->getData()->printNoSpacesString() + ": Deleting node is successful!");
    // Find last node 
    BSTNode* lastNode = findLastNode();
    // Checks to see if nodeToDelete has data, if so deletes it so memory doesn't leak
    if (nodeToDelete->getData() != nullptr) {
        delete nodeToDelete->getData();
    }
    // Assign nodeToDelete a new Currency of the value from lastNode
    nodeToDelete->setData(new Dollar(lastNode->getData()->getCash()));
    // Find the parent of last node and set the pointer to last node to nullptr 
    BSTNode* lastNodesParent = lastNode->getParent();
    if (lastNodesParent->getLeftChild() == lastNode) { 
        lastNodesParent->setLeftChild(nullptr); 
    }
    else if (lastNodesParent->getRightChild() == lastNode) {
        lastNodesParent->setRightChild(nullptr); 
    }
    // Delete lastNode
    delete lastNode; 
    // Percolate down to perserve min heap properties
    percolateDown(nodeToDelete);  
}
/*
    Function to find the last node of a tree
    Pre:    None
    Post:   None
    Return: Returns the last node (last level's rightmost node) of the tree
*/
BSTNode* MinHeap::findLastNode() {
    BSTNode* lastNode = root;
    std::queue<BSTNode*> bstnodeQueue; // Uses std::queue for BSTNode pointers

    bstnodeQueue.push(root);
    while (!bstnodeQueue.empty()) {
        BSTNode* current = bstnodeQueue.front(); 
        lastNode = current; 
        bstnodeQueue.pop();
        // Add the left child to the queue
        if (current->getLeftChild() != nullptr) { 
            bstnodeQueue.push(current->getLeftChild());
        }
        // Add the right child to the queue
        if (current->getRightChild() != nullptr) { 
            bstnodeQueue.push(current->getRightChild());
        }
    }
    //printStatement_WithEndl("Finding last node: " + lastNode->getData()->printNoSpacesString() + ": Node is successfully found");
    return lastNode;  
}
/*
    Percolate downward function to reorganize the min heap after a deletion 
    Pre:    node - the node to percolate down at 
    Post:   The min heap's properties is presevered at the path where it percolates down at
    Return: None
*/
void MinHeap::percolateDown(BSTNode* node) {
    // While the node has a left child that has a smaller dollar than it, or it has a right child that has a smaller dollar than it
    while ( node->getLeftChild() != nullptr && node->getData()->isGreater(*node->getLeftChild()->getData())  
        || node->getRightChild() != nullptr && node->getData()->isGreater(*node->getRightChild()->getData()) ) { 
        // Left Child
        if (node->getLeftChild() != nullptr && node->getData()->isGreater(*node->getLeftChild()->getData())) {
            //Swap 
            Currency* temp = node->getData();
            node->setData(node->getLeftChild()->getData());
            node->getLeftChild()->setData(temp);
            // Move to the left child for the next iteration
            node = node->getLeftChild();
        }
        // Right Child
        else if (node->getRightChild() != nullptr && node->getData()->isGreater(*node->getRightChild()->getData())) {
            //Swap 
            Currency* temp = node->getData();
            node->setData(node->getRightChild()->getData());
            node->getRightChild()->setData(temp);
            // Move to the left child for the next iteration
            node = node->getRightChild();
        }
    }
}

#endif // MINHEAP_H
