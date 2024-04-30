/*
Project Information
Project Name:       Lab 2 - Classes, Inheritance, and Polymorphism
Class:              W24 CIS D022C Data Abstract & Structures 04Y Goel 32936, 34068
Professor:          Manish Goel 
Contributors:       Marlon Huynh, Joseph Silvas
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
#include "pound.h"

using namespace std;

int main() {
    // Declare currency array with default Dollar and Pound objects 
    Currency* moneyArr[2];

    cout << "These are the objects in moneyArr[0] and moneyArr[1]" << endl;
    moneyArr[0] = new Dollar(0.0, "dollar"); // moneyArr[0] is a pointer to default dollar object
    moneyArr[0]->print();
    moneyArr[1] = new Pound(0.0, "pound"); // moneyArr[1] is a pointer to default pound object
    moneyArr[1]->print();
    cout << endl;

    string input;
    bool loop = true;

    while (loop == true) {
        cout << "Input will only accept lowercase letters and numbers." << endl;
        cout << "Enter an input to change Dollar object in moneyArr[0] or Pound object in moneyArr[1]: " << endl;
        getline(cin, input);
        loop = moneyArr[0]->inputThis(moneyArr, input); // Since a reference to the whole array, moneyArr, is inputted here, it doesnt matter if inputThis function is called on moneyArr[0] or moneyArr[1]. It would still work by determining which array object in moneyArr to use.
    }

    // Deallocate moneyArr
    cout << "Deallocating money array..." << endl;
    delete* moneyArr;
    cout << "Deallocated money array!" << endl;

    return 0;
}