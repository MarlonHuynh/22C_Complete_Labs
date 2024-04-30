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

/*
    This is Betty's Lab 2 Dollar file. (Clarification because Betty changed partners)  

    CHANGES MADE IN LAB 3:

    - Reformatted comments a bit for easier reading compared to Lab 2
    - Changed print function so it's better adapted for printing singly-linked lists, queues, and stacks
    - Added a cash only constructor that automatically assigns name with 'Dollar'
    - Implemented default contructor that assigns name with 'Dollar', moneyWhole with 0, and moneyFraction with 0
    - Changed isGreater and isEqual to boolean override functions instead of void override functions

     CHANGES MADE IN LAB 4:
     
    - added more printing methods to help with more streamlined output: 
        void printNoSpaces() const override;
        string printString() const override; 
        string printNoSpacesString() const override; 
    - added boolean method to check for non-negative value
        bool isCashValid(); 

    CHANGES MADE IN LAB 5:

    - Removed the virtual declaration of the add/sub/eq/gr as virtual and override functions in currency.h and dollar.h

*/

#ifndef DOLLAR_H
#define DOLLAR_H

#include "currency.h"

class Dollar : public Currency {
private:
    std::string currencyName;

public:
    // Default constructor
    Dollar() { // Implemented
        currencyName = "Dollar";
        moneyWhole = 0;
        moneyFraction = 0;
    }
    // Cash only constructor
    Dollar(double cash) { // Added
        currencyName = "Dollar"; 
        moneyWhole = static_cast<int>(cash);
        moneyFraction = static_cast<int>((cash - moneyWhole) * 100 + 0.5); // rounding to nearest cent
    };
    // Normal constructor
    Dollar(double cash, const std::string& name){
        currencyName = name;
        moneyWhole = static_cast<int>(cash);
        moneyFraction = static_cast<int>((cash - moneyWhole) * 100 + 0.5); // rounding to nearest cent
    };
    // Copy constructor
    Dollar(const Dollar& other) {
        moneyWhole = other.moneyWhole; 
        moneyFraction = other.moneyFraction; 
        currencyName = other.currencyName;
    };
    // Validity checker for negative values
    bool isCashValid() const override{
        if (moneyWhole >= 0 && moneyFraction >= 0 && currencyName == "Dollar") {
            return true; 
        }
        return false; 
    }
    // Destructor
    ~Dollar() override {}
    // Operate the intruction provided
    void OperateInstructionInDerived(char operation, double cash, std::string objType) override;
    // Print
    void print() const override;  
    void printNoSpaces() const override; 
    std::string printString() const override; 
    std::string printNoSpacesString() const override;
};
/*
    Function that processes cash and object type inputted and creates a pointer to an object based on that input, then calls the add/subtract functions.
    Pre:    operation - char which stores the instruction (either 'a' for addition or 's' for subtraction)
            cash - double of the amount of cash of the object the user wants to add or subtract
            objType - string of the type of object the user wants to add (either "dollar" or "pound")
    Post:   Changes the current object's moneyWhole and moneyFraction values and prints the resulting values of the class after the addition/subtraction operation
    Return: none
*/
void Dollar::OperateInstructionInDerived(char operation, double cash, std::string objType) {
    if (operation == 'a') {
        Dollar* d = new Dollar(cash, objType);
        add(*d);
        delete d;
        print();
    }
    else if (operation == 's') {
        Dollar* d = new Dollar(cash, objType);
        subtract(*d);
        delete d;
        print();
    }
}
/*
    Functions that prints the value of the dollar object
    Pre:    None
    Post:   Prints moneyWhole, moneyFraction, and currencyName in the format xx.xx [currencyName] to console
    Return: None
*/
void Dollar::print() const { 
    std::cout << "   " << getMoneyWhole() << "." << getMoneyFraction() << " " << currencyName;
}
void Dollar::printNoSpaces() const {
    std::cout << getMoneyWhole() << "." << getMoneyFraction() << " " << currencyName;
}

std::string Dollar::printString() const{
    std::string str = "   " + std::to_string(getMoneyWhole()) + "." + std::to_string(getMoneyFraction()) + " " + currencyName;
    return str; 
}
std::string Dollar::printNoSpacesString() const {
    std::string str = std::to_string(getMoneyWhole()) + "." + std::to_string(getMoneyFraction()) + " " + currencyName;
    return str;
}
    
#endif // DOLLAR_H