/*
Project Information
Project Name:       Lab 2 - Classes, Inheritance, and Polymorphism
Class:              W24 CIS D022C Data Abstract & Structures 04Y Goel 32936, 34068
Professor:          Manish Goel
Contributors:       Betty Huynh, Joseph Silvas
Date Due:           Feb 7th, 2024

Program Information
IDE Used:           Visual Studio 2022
Language:           C++
*/

#ifndef CURRENCY_H
#define CURRENCY_H

class Currency { // This function is abstract and cannot be instaniated directly
protected:
    int moneyWhole;
    int moneyFraction;

public:
    // Default constructor
    Currency(){moneyWhole = 0; moneyFraction=0;}
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
    // Virtual add
    virtual void add(Currency& other) = 0;
    // Virtual subtract 
    virtual void subtract(Currency& other) = 0;
    // Virtual isEqual
    virtual void isEqual(const Currency& other) = 0;
    // Virtual isGreater
    virtual void isGreater(const Currency& other) = 0;
    // Getters
    int getMoneyWhole() const;
    int getMoneyFraction() const;
    // Setters
    void setMoneyWhole(int i);
    void setMoneyFraction(int i);
    // Print
    virtual void print() const = 0;
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