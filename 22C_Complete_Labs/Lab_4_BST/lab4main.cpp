/*
Project Information
Project Name:       Lab 4 - Binary Search Tree
Class:              W24 CIS D022C Data Abstract & Structures 04Y Goel 32936, 34068
Professor:          Manish Goel
Contributors:       Betty Huynh, Jorge David Olivas-Galdamez
Date Due:           March 2nd, 2024

Program Information
IDE Used:           Visual Studio 2022
Language:           C++
*/

#include <iostream>
#include <sstream>
#include <string> 
#include <fstream>

#include "currency.h"
#include "dollar.h" 
#include "linknode.h"
#include "singlylinkedlist.h"
#include "queue.h"
#include "stack.h"
#include "BSTNode.h"
#include "BST.h"

#define _CRTDBG_MAP_ALLOC // To see memory leaks in Visual Studio 

using namespace std;
 
int main() {

    // Welcome message
    std::cout << "******************************************************";
    std::cout << "\n\tWelcome to the binary tree demonstration!";
    std::cout << "\n\nContributors: Betty Huynh, Jorge David Olivas-Galdamez\nIDE Used: Visual Studio 2022\nLanguage: C++";
    std::cout << "\n******************************************************\n\n"; 
    
    // Create tree
    BST* bst = new BST; 

    // Populating tree
    bst->insert(57.12);
    bst->insert(23.44); 
    bst->insert(87.43);
    bst->insert(68.99);
    bst->insert(111.22);
    bst->insert(44.55);
    bst->insert(77.77);
    bst->insert(18.36);
    bst->insert(543.21);
    bst->insert(20.21);
    bst->insert(345.67);
    bst->insert(36.18);
    bst->insert(48.48);
    bst->insert(101.00);
    bst->insert(11.00);
    bst->insert(21.00);
    bst->insert(51.00);
    bst->insert(1.00);
    bst->insert(251.00);
    bst->insert(151.00);

    //  Print initial tree
    bst->traverseByLevel();
    bst->traverseInOrder();
    bst->traversePreOrder();
    bst->traversePostOrder();
   
    // Interactivity 
    { // Limit the scope of string so Visual Studio's _CrtDumpMemoryLeaks memory detection doesn't detect a leak as it is called before the program ends
        string inp = "";
        string inp2 = "";
        double num = 0;
        while (inp != "exit" && inp != "quit") {
            std::cout << "Type: 'add [number]'      to add object to tree" << endl;
            std::cout << "Type: 'search [number]'   to search object in tree" << endl;
            std::cout << "Type: 'delete [number]'   to delete object in tree" << endl;
            std::cout << "Type: 'print level'       to print using by level traversal to the console and output test file" << endl;
            std::cout << "Type: 'print inorder'     to print using inorder traversal to the console and output test file" << endl;
            std::cout << "Type: 'print preorder'    to print using preorder traversal to the console and output test file" << endl;
            std::cout << "Type: 'print postorder'   to print using postorder traversal to the console and output test file" << endl;
            std::cout << "Type: 'print all'         to print using all 4 traversal methods to the console and output test file" << endl;
            std::cout << "Type: 'exit' or 'quit'     to exit program" << endl;
            std::cout << "\nEnter: " << endl;
            cin >> inp;

            if (inp == "add") {
                cin >> ws >> num;
                bst->insert(num);
            }
            else if (inp == "search") {
                cin >> ws >> num;
                bst->search(num); 
            }
            else if (inp == "delete") {
                cin >> ws >> num;
                bst->deleteNode(num); 
            }
            else if (inp == "print") {
                cin >> ws >> inp2;
                if (inp2 == "level") {
                    bst->traverseByLevel();
                }
                else if (inp2 == "inorder") {
                    bst->traverseInOrder();
                }
                else if (inp2 == "preorder") {
                    bst->traversePreOrder();
                }
                else if (inp2 == "postorder") {
                    bst->traversePostOrder();
                }
                else if (inp2 == "all") {
                    bst->traverseAllMethods(); 
                }
            }
        }
    }
 
    std::cout << "\n\n*******************************************\n\tMemory Checks\n*******************************************\n";
    
    delete bst;

    // To see memory leaks in Visual Studio
#ifdef _MSC_VER
    printf(_CrtDumpMemoryLeaks() ? "Memory Leak using _CrtDumpMemoryLeaks\n" : "No Memory Leak using _CrtDumpMemoryLeaks\n");
#endif

    std::cout << "\nThanks for using the ADTs demonstration program!\n";
    
    return 0;

}
