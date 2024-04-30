/*
Project Information
Project Name:       Lab 5 - Hashtables
Class:              W24 CIS D022C Data Abstract & Structures 04Y Goel 32936, 34068
Professor:          Manish Goel
Contributors:       Betty Huynh, Jorge David Olivas-Galdamez
Date Due:           March 17th, 2024

Program Information
IDE Used:           Visual Studio 2022
Language:           C++
*/

/*
    This is Betty's Lab 2 Dollar file. (Clarification because Betty changed partners)  

    CHANGES MADE IN LAB 3:

    - Reformatted comments a bit for easier reading compared to Lab 2
    - Changed isGreater and isEqual to boolean virtual functions instead of void virtual functions

    CHANGES MADE IN LAB 4:
     
    - added more printing methods to help with more streamlined output: 
        virtual void printNoSpaces() const = 0;
        virtual string printString() const = 0;
        virtual string printNoSpacesString() const = 0;
    - added boolean method to check for non-negative cash value
        virtual bool isCashValid() const = 0;

    CHANGES MADE IN LAB 5:
     
    - Removed the virtual declaration of the add/sub/eq/gr as virtual and override functions in currency.h and dollar.h

*/
#ifndef CURRENCY_H
#define CURRENCY_H
#include <string>
#include <iostream>
#include <iomanip>


class Currency { // This function is abstract and cannot be instaniated directly
protected:
    int moneyWhole;
    int moneyFraction;

public:
    // Default constructor
    Currency(){ moneyWhole = 0; moneyFraction=0 ; }
    // Normal constructor
    Currency(double cash){
        moneyWhole = int(cash); // Calculates moneyWhole and moneyFraction if moneyFraction > 100. (100 moneyFraction = 1 moneyWhole) 
        moneyFraction = (cash-double(moneyWhole))*100;
    }
    // Copy constructor
    Currency(const Currency& other){
        moneyWhole=other.moneyWhole; moneyFraction=other.moneyFraction;
    };
    // Virtual destructor
    virtual ~Currency() {} // Overwritten destructors of the derived class has to has it's own name.
    // Checks if cash is non-negative
    virtual bool isCashValid() const = 0; 
    // add
    void add(Currency& other);
    // subtract 
    void subtract(Currency& other);
    // isEqual
    bool isEqual(const Currency& other); // Changed to Boolean
    // isGreater
    bool isGreater(const Currency& other); // Changed to Boolean
    // Getters
    int getMoneyWhole() const;
    int getMoneyFraction() const; 
    // Setters
    void setMoneyWhole(int i);
    void setMoneyFraction(int i); 
    // Print
    virtual void print() const = 0;
    virtual void printNoSpaces() const = 0;
    virtual std::string printString() const = 0;
    virtual std::string printNoSpacesString() const = 0;
    // Function that controls the logic turning the input into commands for the currency array
    bool inputThis(Currency** arr, std::string inp); 
    // Function to separate variables from a input string and calls OperateInstructionInDerived
    void getInstructionVars(const std::string input);
    // Virtual function to perform operations in derived class (uses currencyName so it has to be a virtual function in derived class) 
    virtual void OperateInstructionInDerived(char operation, double cash, std::string objType) = 0;
    // Function to check validity of input string function and throws cerr errors if neccessary 
    bool checkInputValid(const std:: string str);
};
/*
    Function that adds values to the Dollar's whole and fractional ints
    Pre:    other - the other Currency to add to current object
    Post:   Edits the object's moneyWhole or moneyFraction or prints an error statement if result is negative
    Return: None
*/
void Currency::add(Currency& other) {
    if (other.getMoneyFraction() < 10 && other.getMoneyFraction() >= 1) { // If fractional part is 0.5, turns into 50 cent instead of 5 cent
        other.setMoneyFraction(other.getMoneyFraction() * 10);
    }
    int totalWhole = getMoneyWhole() + other.getMoneyWhole();
    int totalFraction = getMoneyFraction() + other.getMoneyFraction();
    if (totalFraction >= 100) {
        totalWhole += totalFraction / 100; // Carry over to whole if fractional part exceeds 100
        totalFraction %= 100; // Update fractional part
    }
    if (totalWhole < 0 || totalFraction < 0) { // Check if result is negative
        std::cerr << "Error: Resulting addition result cannot be a negative number!" << std::endl;
    }
    else { // If result isn't negative, update the current object's moneyWhole and moneyFraction
        setMoneyWhole(totalWhole);
        setMoneyFraction(totalFraction);
    }
}
/*
    Function that subtract values to the class' whole and fractional ints
    Pre:    other - the other Currency to subtract from current object
    Post:   Edits the object's moneyWhole or moneyFraction or prints an error statement if result is negative
    Return: None
*/
void Currency::subtract(Currency& other) {
    if (other.getMoneyFraction() < 10 && other.getMoneyFraction() >= 1) { // If fractional part is 0.5, turns into 50 cent instead of 5 cent
        other.setMoneyFraction(other.getMoneyFraction() * 10);
    }
    // Subtract the moneyWhole and moneyFraction of the 'other' Currency object from the current object
    int totalWhole = getMoneyWhole() - other.getMoneyWhole();
    int totalFraction = getMoneyFraction() - other.getMoneyFraction();
    // Adjust the result if necessary (borrow from the whole part if the fraction becomes negative)
    while (totalFraction < 0) {
        totalWhole -= 1;
        totalFraction += 100;
    }
    if (totalWhole < 0 || totalFraction < 0) { // Check if result is negative
        std::cerr << "Error: Resulting subtraction result cannot be a negative number!" << std::endl;
    }
    else { // If result isn't negative, update the current object's moneyWhole and moneyFraction
        setMoneyWhole(totalWhole);
        setMoneyFraction(totalFraction);
    }
}
/*
    Function that checks if two Dollar objects are equal
    Pre:    other - the other Currency to to be compared
    Post:   prints a statement whether two Currency object have equal moneyWhole and moneyFraction variables
    Return: None
*/
bool Currency::isEqual(const Currency& other) { // Changed to bool instead of void
    if (other.getMoneyWhole() == moneyWhole && other.getMoneyFraction() == moneyFraction) {
        //std::cout << "The numbers are equal." << std::endl;
        return true;
    }
    //std::cout << "The numbers are not equal." << std::endl;
    return false;
};
/*
    Function that checks if the current Dollar is greater than or less than the compared object
    Pre:    other - the other Currency to to be compared
    Post:   prints a statement whether the current Currency object greater or less than moneyWhole and moneyFraction variables from the compared object
    Return: None
*/
bool Currency::isGreater(const Currency& other) { // Changed to bool instead of void
    if (other.getMoneyWhole() > moneyWhole || other.getMoneyWhole() == moneyWhole && other.getMoneyFraction() >= moneyFraction) {
        //std::cout << "Dollar stored in the array is less than/equal to the compared dollar." << std::endl;
        return false;
    }
    //std::cout << "Dollar stored in the array is greater than the compared dollar.." << std::endl;
    return true;
};
/*
    Getter functions that retrieves the object's moneyWhole or moneyFraction
    Pre:    None
    Post:   None
    Return: int of the moneyWhole or moneyFraction variable
*/
int Currency::getMoneyWhole() const { return moneyWhole; }
int Currency::getMoneyFraction() const { return moneyFraction; } 
/*
    Setter functions that changes the object's moneyWhole or moneyFraction to set value
    Pre:    i = int to change moneyWhole or moneyFraction to 
    Post:   Changes the moneyWhole or moneyFraction of the current object
    Return: None
*/
void Currency::setMoneyWhole(int i) { moneyWhole = i; }
void Currency::setMoneyFraction(int i) { moneyFraction = i; } 

/*
    Function that takes a currency array and a string input and implements the logic in checking the validity of the input and perform actions on a specified object in the currency array. This functions returns true or false to the looping variable in main so that if 'q' is an input, the loop will stop and program will exit.
    Pre:    arr - pointer to the pointer of array of Currency objects to make changes to
            inp - string of input to get instructions from and operate with
    Post:   Performs inputted instructions on the arr array if the input string is valid and prints the Currency array. Assumes the Currency array only has 2 objects
    Return: True or false determining whether to keep looping the while loop in main (only false if input is 'q' for quit)
*/
bool Currency::inputThis(Currency** arr, std::string inp) {
    // Variables
    std::istringstream iss(inp);
    char operation;
    char type;
    iss >> std::ws >> operation >> std::ws >> type;

    bool validity = (*arr)->checkInputValid(inp); // Checks the validity of the input string and prints any error
    if (validity == true) {
        if (operation == 'q') { // Assigns looping variable in main to false if input is 'q' 
            return false;
        }
        if (type == 'd') { // Operate on the dollar object and prints the dollar and pound object
            (*arr)->getInstructionVars(inp);
            (*(arr + 1))->print();
        }
        else if (type == 'p') { // Operate on the pound object and prints the dollar and pound object
            (*arr)->print();
            (*(arr + 1))->getInstructionVars(inp);
        }
        std::cout << std::endl;
    }
    else if (validity == false) { // Even if validity is false, prints the dollar and pound object
        (*arr)->print();
        (*(arr + 1))->print();
        std::cout << std::endl;
    }
    return true; // Assigns looping variable in main to true so it can get another input
}
/*
    Function meant to take user input separates it into usable variables of correct type, then calls the OperateInstructionInDerived which performs an operation on the current object
    Pre:    input - string, assumed to be a valid string
    Post:   calls OperateInstructionInDerived, which is performs some action on the specified currency object.
    Return: None
*/
void Currency::getInstructionVars(const std::string input) {
    // Variables
    std::istringstream iss;
    char operation, arrType;
    std::string objType;
    int wholePart;
    int fracPart;
    double cash;
    char dot;
    // Initialize variables
    iss.str(input);
    iss >> std::ws >> operation;
    iss >> std::ws >> arrType;
    iss >> wholePart;
    if (!(iss >> dot)) { fracPart = 0; } // If dot does not exist, fraction part is 0.
    iss >> fracPart;
    // Combine the integer and decimal parts into a double
    cash = wholePart + (static_cast<double>(fracPart) / 100); // Assuming decimalPart represents two decimal places
    iss >> std::ws >> objType;
    if (arrType == 'd' || arrType == 'p') { // Operate using the default dollar variable or default pound variable
        OperateInstructionInDerived(operation, cash, objType);
    }
};
/*
    Function that checks if the string is valid, if not, throw a cerr error
    Pre:    str - string to check if its valid
    Post:   Prints an error if input validation fails
    Return: True or false to determine if the string is valid or not
*/
bool Currency::checkInputValid(const std::string str) {
    std::istringstream iss(str);
    char str1, str2;
    std::string str3;
    int wholePart; // OK to have these two parts as ints instead of one double for the purpose of checking validity
    int fracPart;
    char dot;
    if (!(iss >> std::ws >> str1)) { std::cerr << "Error: First string not found!" << std::endl; return false; }
    if (str1 == 'q') { return true; } // Special case to return true when 'q' is encountered
    if (str1 != 'a' && str1 != 's') { std::cerr << "Error: First string must be 'a' or 's'!" << std::endl; return false; }
    if (!(iss >> std::ws >> str2)) { std::cerr << "Error: Second string not found!" << std::endl; return false; }
    if (str2 != 'p' && str2 != 'd') { std::cerr << "Error: Second string must be 'p' or 'd'!" << std::endl; return false; }
    if (!(iss >> wholePart)) { std::cerr << "Error: Integer part not found!" << std::endl; return false; }
    if (iss.peek() == '.') { // Check if next character is a dot
        iss >> dot; // If dot found, read it
        if (!(iss >> fracPart)) { // Check if there's a fractional part after dot
            std::cerr << "Error: Fractional part not found after dot!" << std::endl;
            return false;
        }
    }
    if (!(iss >> std::ws >> str3)) { std::cerr << "Error: Third string not found!" << std::endl; return false; }
    std::string remaining; 
    if (iss >> remaining) { std::cerr << "Error: Extra input found after parsing!" << std::endl; return false; }
    // Checks if str2 and str3 match (prevents adding Dollar to Pound object and vice versa)
    if (str2 == 'd' && str3 != "dollar") { std::cerr << "Error: Cannot attempt to add " << str3 << " to Dollar object in array! If you did enter dollar, please make sure dollar is all lowercase." << std::endl; return false; }
    if (str2 == 'p' && str3 != "pound") { std::cerr << "Error: Cannot attempt to add " << str3 << " to Pound object in array! If you did enter pound, please make sure pound is all lowercase." << std::endl; return false; }   
    // If all checks pass, return true
    return true;
};

#endif // CURRENCY_H