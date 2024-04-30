/*
Project Information
Project Name:       Lab 4 - Binary Search Tree
Class:              W24 CIS D022C Data Abstract & Structures 04Y Goel 32936, 34068
Professor:          Manish Goel
Contributors:       Marlon Huynh, Jorge David Olivas-Galdamez
Date Due:           March 2nd, 2024

Program Information
IDE Used:           Visual Studio 2022
Language:           C++
*/

#ifndef BST_H
#define BST_H

#include <iostream> 
#include <fstream>

#include "Currency.h"
#include "Dollar.h"
#include "BSTNode.h"
#include "Queue.h" 

class BST {
private:
    BSTNode* root;
public:
    // Construction
    BST();                              
    BST(BSTNode* newRoot);              
    // Destruction
    ~BST();                             
    void destroyTree(BSTNode* node);    
    // Insertion
    void insert(double cash);
    BSTNode* insertRecursive(BSTNode* node, Currency* newData); 
    // Inorder traversal
    void traverseInOrder();
    void traverseInOrderRecursive(BSTNode* node); 
    // Preorder traversal
    void traversePreOrder();
    void traversePreOrderRecursive(BSTNode* node); 
    // Postorder traversal
    void traversePostOrder();
    void traversePostOrderRecursive(BSTNode* node); 
    // By level traversal
    void traverseByLevel();
    void traverseByLevelHelper(BSTNode* traversalRoot, Queue& queue, int level);
    int getHeight(BSTNode* node);
    // Traverse using all 4 methods
    void traverseAllMethods();
    // Search
    bool search(double cash);
    bool search_withoutPrintingResult(double cash);
    bool searchHelperRecursive(BSTNode* node, Currency* dollarObj); 
    // Deletion
    void deleteNode(double cash);
    BSTNode* deleteRecursive(BSTNode* node, Currency* dollarObj);
    BSTNode* minValueNode(BSTNode* node); 
    // Printing 
    void printOneEndl(); 
    void printOneSpace(); 
    void printStatement_WithEndl(std::string strToPrint); 
    void printStatement_WithNoEndl(std::string strToPrint); 
};
/*
    Constructors of the binary tree
    Pre:    None or a BSTNode newRoot
    Post:   Assigns root to nullptr/BSTNode newRoot and clears the output.txt file in anticipation of new data being written 
    Return: None
*/
BST::BST(){
    root = nullptr;
    std::ofstream outputFile("output.txt", std::ios::trunc);    // Truncates the output file to an empty file to prep for the appending of new print content
    outputFile.close();                                         
}
BST::BST(BSTNode* newRoot) {
    root = newRoot;
    std::ofstream outputFile("output.txt", std::ios::trunc);    // Truncates the output file to an empty file to prep for the appending of new print content
    outputFile.close();                                        
}
/*
    Destructor of the binary tree
    Pre:    None 
    Post:   The tree is destroyed
    Return: None
*/
// Destructor
BST::~BST() {
    destroyTree(root);
}
/*
    Recursive helper function of the destructor
    Pre:    None
    Post:   Every time the function is called, if node inputted is not nullptr, calls destroyTree on leftchild and rightchild, then destroys the node. 
    Return: None
*/
void BST::destroyTree(BSTNode* node) {
    if (node != nullptr) {
        destroyTree(node->getLeftChild());
        destroyTree(node->getRightChild());
        delete node;
    }
}
/*
    Insertion of a new node in the binary tree
    Pre:    cash - a double representing the cash value 
    Post:   A new node of value cash is added to the binary tree if no other node with the same data exists
    Return: None
*/
void BST::insert(double cash) {
    Currency* targetDollar = new Dollar(cash); 
    if (targetDollar->isCashValid() == true) {
        root = insertRecursive(root, targetDollar);
    }
    else {
        printStatement_WithEndl("Inserting " + targetDollar->printNoSpacesString() + ": Node is unsuccessfully added. Cannot be a negative value."); 
    }
}
/*
    Recursive helper function of the insertion
    Pre:    node - the current BSTNode to compare the new data being inserted against
            targetDollar - the Dollar object to be inserted
    Post:   Inserts a new node with data of the new Currency object if there are no nodes with the same Currency value
    Return: The updated root node
*/
BSTNode* BST::insertRecursive(BSTNode* node, Currency* targetDollar) {
    if (node == nullptr) { // Checks if the node is empty
        node = new BSTNode(targetDollar);
        printStatement_WithEndl("Inserting " + targetDollar->printNoSpacesString() + ": Node is successfully added");
        return node;
    }
    else if (node->getData()->isEqual(*targetDollar)) { // Checks if the node has the same value
        printStatement_WithEndl("Inserting " + targetDollar->printNoSpacesString() + ": Node is unsuccessfully added. Node with the same data already exists.");
    }
    else if (node->getData()->isGreater(*targetDollar)) { // Checks if the node is greater than target dollar, if so, the target must be inserted into the left subtree
        node->setLeftChild(insertRecursive(node->getLeftChild(), targetDollar));
    }
    else if (targetDollar->isGreater(*(node->getData()))) { // Checks if the target dollar is less than target node, if so, the target must be inserted into the right subtree
        node->setRightChild(insertRecursive(node->getRightChild(), targetDollar));
    }
    return node; // If all other cases failed, then returns the node
}
/*
    Traverses the tree in order
    Pre:    None
    Post:   For each node, the node's data is printed along with an endl
    Return: None
*/
void BST::traverseInOrder() {
    printStatement_WithEndl("In-Order Traversal");
    traverseInOrderRecursive(root);
    printOneEndl();
}
/*
    Recursive helper function of traversal in order function
    Pre:    node - the root node of the tree to traverse through
    Post:   Calls traverseInOrderRecurive on the left child, then prints node's current data if not null, then calls traverseInOrderRecursive on the right child
    Return: None
*/
void BST::traverseInOrderRecursive(BSTNode* node) {
    if (node != nullptr) {
        traverseInOrderRecursive(node->getLeftChild());
        if (node->getData() != nullptr) {
            printStatement_WithEndl(node->getData()->printString());
        }
        traverseInOrderRecursive(node->getRightChild());
    }
}
/*
    Traverses the tree in pre order
    Pre:    None
    Post:   For each node, the node's data is printed along with an endl
    Return: None
*/
void BST::traversePreOrder() {
    printStatement_WithEndl("Pre-Order Traversal: ");
    traversePreOrderRecursive(root);
    printOneEndl();
}
/*
    Recursive helper function of traversal pre order function
    Pre:    node - the root node of the tree to traverse through
    Post:   Prints the node's current data, Calls traversePrerderRecurive on the left child, then calls traversePreOrderRecursive on the right child
    Return: None
*/
void BST::traversePreOrderRecursive(BSTNode* node) {
    if (node != nullptr) {
        printStatement_WithEndl(node->getData()->printString());
        traversePreOrderRecursive(node->getLeftChild());
        traversePreOrderRecursive(node->getRightChild());
    }
}
/*
    Traverses the tree in post order
    Pre:    None
    Post:   For each node, the node's data is printed along with an endl
    Return: None
*/
void BST::traversePostOrder() {
    printStatement_WithEndl("Post-Order Traversal: ");
    traversePostOrderRecursive(root);
    printOneEndl();

}
/*
    Recursive helper function of traversal post order function
    Pre:    node - the root node of the tree to traverse through
    Post:   Calls traversePostOrderRecurive on the left child, then calls traversePostOrderRecursive on the right child, then prints the node's current data,
    Return: None
*/
void BST::traversePostOrderRecursive(BSTNode* node) {
    if (node != nullptr) {
        traversePostOrderRecursive(node->getLeftChild());
        traversePostOrderRecursive(node->getRightChild());
        // Print current data
        printStatement_WithEndl(node->getData()->printString());
    }
}
/*
    Traverses the tree by level
    Pre:    None
    Post:   For each node, the node's data is printed along with an endl
    Return: None
*/
void BST::traverseByLevel() {

    printOneEndl();

    BSTNode* thisroot = root;
    int height = getHeight(thisroot);
    Queue queue; // Extra credit: Currency queue used from lab 3 without motification

    printStatement_WithEndl("Printing by level: ");
    for (int i = 1; i <= height; ++i) {
        traverseByLevelHelper(thisroot, queue, i);
        printStatement_WithNoEndl("Level " + std::to_string(i) + ": ");
        while (!queue.isQueueEmpty()) {
            printStatement_WithNoEndl(queue.dequeue()->printNoSpacesString());
            printOneSpace();
        }
        printOneEndl();
    }
    printOneEndl();
}
/*
    Recursive helper function of the traverses by level function
    Pre:    traversalRoot - the BSTNode to start traversal with
            queue - the Currency queue to add to to dequeue later to print
            level - the height of the current node
    Post:   queue is filled with nodes of the same level 
    Return: None
*/
void BST::traverseByLevelHelper(BSTNode* traversalRoot, Queue& queue, int level) {
    if (traversalRoot == nullptr)
        return;

    if (level == 1) {
        queue.enqueue(traversalRoot->getData());
    }
    else if (level > 1) {
        traverseByLevelHelper(traversalRoot->getLeftChild(), queue, level - 1);
        traverseByLevelHelper(traversalRoot->getRightChild(), queue, level - 1);
    }
}
/*
    Gets the height of a node recursively (Used in traversal by level) 
    Pre: node - the node to get height of
    Post: None
    Return: Integer of the height of the node
*/
int BST::getHeight(BSTNode* node) {
    if (node == nullptr)
        return 0;
    else {
        int leftHeight = getHeight(node->getLeftChild());
        int rightHeight = getHeight(node->getRightChild());
        return std::max(leftHeight, rightHeight) + 1;
    }
}
/*
    Searches for a value 
    Pre:    cash - the cash double to search for 
    Post:   Prints search result
    Return: True or false determining if there is a node of the same data in the tree or not
*/
bool BST::search(double cash) {
    Currency* dollarToSearchFor = new Dollar(cash);
    bool exists = searchHelperRecursive(root, dollarToSearchFor);

    if (exists) {
        printStatement_WithEndl("Searching for " + dollarToSearchFor->printNoSpacesString() + ": Node is found in tree!");
    }
    else {
        printStatement_WithEndl("Searching for " + dollarToSearchFor->printNoSpacesString() + ": Node is not found in tree!");
    }

    delete dollarToSearchFor;
    return exists;
}
/*
    Searches for a value [ Same as search(double cash) but without printing the result ], used in deleting function
    Pre:    cash - the cash double to search for
    Post:   None
    Return: True or false determining if there is a node of the same data in the tree or not
*/
bool BST::search_withoutPrintingResult(double cash) {
    Currency* dollarToSearchFor = new Dollar(cash);
    bool exists = searchHelperRecursive(root, dollarToSearchFor);
    delete dollarToSearchFor;
    return exists;
}
/*
    Recursive helper function of the search function
    Pre:    node - the current node 
            targetDollar - the target dollar object to search for
    Post:   None
    Return: True or false determining if there is a node of the same data in the tree or not
*/
bool BST::searchHelperRecursive(BSTNode* node, Currency* targetDollar) {
    if (node == nullptr) { // If current node is nullptr, returns false
        return false;
    }
    else if (node->getData()->isEqual(*targetDollar)) { // If current node has same dollar value, return true
        return true;
    }
    else if (node->getData()->isGreater(*targetDollar)) { // If current node is greater than target, call searchHelperRecursive on the left child 
        return searchHelperRecursive(node->getLeftChild(), targetDollar);

    }
    else if (targetDollar->isGreater(*node->getData())) { // If Target is greater than the current node, call searchHelperRecursive on the right child 
        return searchHelperRecursive(node->getRightChild(), targetDollar);
    }
    else { // If value not found throughout entire tree
        return false;
    }
}
/*
    Deletes a node from tree
    Pre:    cash - the value of the node to delete 
    Post:   A node of the same cash value from the tree is deleted if it exists
    Return: None
*/
void BST::deleteNode(double cash) {

    Currency* dollarToDelete = new Dollar(cash);
    bool deletable = search_withoutPrintingResult(cash);
    if (deletable) {
        printStatement_WithEndl("Deleting " + dollarToDelete->printNoSpacesString() + ": Node is deleted successfully!!");
    }
    else {
        printStatement_WithEndl("Deleting " + dollarToDelete->printNoSpacesString() + ": Node is deleted unsuccessfully! Could not find node in tree!");
    }
    root = deleteRecursive(root, dollarToDelete);
    delete dollarToDelete;
}
/*
    Recursive helper function of the delete function
    Pre:    node - the current node
            targetDollar - the dollar value of the node to search for and delete
    Post:   A node of the same cash value from the tree is deleted if it exists
    Return: Updated root node
*/
BSTNode* BST::deleteRecursive(BSTNode* node, Currency* targetDollar) {
    if (node == nullptr) { // If the node is nullptr
        return nullptr;
    }
    if (node->getData()->isGreater(*targetDollar)) { // If the node is greater than the target dollar
        node->setLeftChild(deleteRecursive(node->getLeftChild(), targetDollar));
    }
    else if (targetDollar->isGreater(*(node->getData()))) { // If the target dollar is greater than the node
        node->setRightChild(deleteRecursive(node->getRightChild(), targetDollar));
    }
    else { // Node to delete found
        if (node->getLeftChild() == nullptr) { // Deletes right children
            BSTNode* rightChild = node->getRightChild();
            delete node;
            return rightChild;
        }
        else if (node->getRightChild() == nullptr) { // Deletes left childtren
            BSTNode* leftChild = node->getLeftChild();
            delete node;
            return leftChild;
        }
        else { // Node has two children
            // Find the inorder successor (smallest node in the right subtree)
            BSTNode* successor = minValueNode(node->getRightChild());
            // Copy the inorder successor's content to this node 
            node->getData()->setMoneyWhole(successor->getData()->getMoneyWhole());
            node->getData()->setMoneyFraction(successor->getData()->getMoneyFraction());
            // Delete the inorder successor
            node->setRightChild(deleteRecursive(node->getRightChild(), successor->getData()));
        }
    }
    return node;
}
/*
    Finds the minimum value node of a given subtree starting at node
    Pre:    node - the root node of the tree to search in
    Post:   Node
    Return: The node with the smallest value
*/
BSTNode* BST::minValueNode(BSTNode* node) {
    BSTNode* current = node;
    // Loop down to find the leftmost leaf
    while (current->getLeftChild() != nullptr) {
        current = current->getLeftChild();
    }
    return current;
}
/*
    Calls all traversal methods 
    Pre:    None
    Post:   Print using all traversal methods
    Return: None
*/
void BST::traverseAllMethods() {
    printOneEndl();
    traverseByLevel();
    traverseInOrder();
    traversePreOrder();
    traversePostOrder();
}
/*
    Prints one endl line in console and output file
    Pre:    None
    Post:   Prints one endl line in console and output file
    Return: None
*/
void BST::printOneEndl() {
    // Print in console
    std::cout << std::endl;
    // Print in output file
    std::ofstream outputFile("output.txt", std::ios_base::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Failed to open output file." << std::endl;
        return;
    }
    else {
        outputFile << std::endl;
    }
    outputFile.close();
}
/*
    Prints one space in console and output file
    Pre:    None
    Post:   Prints one space in console and output file
    Return: None
*/
void BST::printOneSpace() {
    // Print in console
    std::cout << " ";
    // Print in output file
    std::ofstream outputFile("output.txt", std::ios_base::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Failed to open output file." << std::endl;
        return;
    }
    else {
        outputFile << " ";
    }
    outputFile.close();
}
/*
    Prints a statement with an endl line after in console and output file
    Pre:    strToPrint - the string of the statement to print
    Post:   Prints a statement with an endl line after
    Return: None
*/
void BST::printStatement_WithEndl(std::string strToPrint) {
    // Print in console
    std::cout << strToPrint << std::endl;
    // Print in output file
    std::ofstream outputFile("output.txt", std::ios_base::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Failed to open output file." << std::endl;
        return;
    }
    else {
        outputFile << strToPrint << std::endl;
    }
    outputFile.close();
}
/*
    Prints a statement in console and output file
    Pre:    strToPrint - the string of the statement to print
    Post:   Prints a statement in console and output file
    Return: None
*/
void BST::printStatement_WithNoEndl(std::string strToPrint) {
    // Print in console
    std::cout << strToPrint;
    // Print in output file
    std::ofstream outputFile("output.txt", std::ios_base::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Failed to open output file." << std::endl;
        return;
    }
    else {
        outputFile << strToPrint;
    }
    outputFile.close();
}

#endif // BST_H
