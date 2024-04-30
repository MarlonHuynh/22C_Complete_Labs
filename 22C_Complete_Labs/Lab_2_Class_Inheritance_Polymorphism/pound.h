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

#ifndef POUND_H
#define POUND_H

#include "currency.h"

class Pound : public Currency {
private:
    std::string currencyName;
public:
    // Default constructor
    Pound() :
        Currency(), currencyName("pound") {}
    // Normal constructor
    Pound(double cash, const std::string& name){
        currencyName = name;
        moneyWhole = static_cast<int>(cash);
        moneyFraction = static_cast<int>((cash - moneyWhole) * 100 + 0.5); // rounding to nearest cent
    };
    // Copy constructor
    Pound(const Pound& other){
        moneyWhole = other.moneyWhole; moneyFraction = other.moneyFraction; currencyName = other.currencyName;
    }
    // Destructor
    ~Pound() override {}
    // Add
    void add(Currency& other) override;     
    // Subtract
    void subtract(Currency& other) override;
    // isEqual
    void isEqual(const Currency& other) override;
    // isGreater
    void isGreater(const Currency& other) override;
    // Operate the intruction provided
    void OperateInstructionInDerived(char operation, double cash, std::string objType) override;
    // Print
    void print() const override;
};
/*
    Function that adds values to the Pound's whole and fractional ints
    Pre:    other - the other Currency to add to current object
    Post:   Edits the object's moneyWhole or moneyFraction or prints an error statement if result is negative
    Return: None
*/
void Pound::add(Currency& other) {
    if (other.getMoneyFraction() < 10 && other.getMoneyFraction() >= 1) {
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
    Function that subtract values to the clas' whole and fractional ints
    Pre:    other - the other Currency to subtract from current object
    Post:   Edits the object's moneyWhole or moneyFraction or prints an error statement if result is negative
    Return: None
*/
void Pound::subtract(Currency& other) {
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
    Function that checks if two Pound objects are equal
    Pre:    other - the other Currency to to be compared
    Post:   prints a statement whether two Currency object have equal moneyWhole and moneyFraction variables
    Return: None
*/
void Pound::isEqual(const Currency& other) {
    if (other.getMoneyWhole() == moneyWhole && other.getMoneyFraction() == moneyFraction){
        std::cout << "The numbers are equal." << std::endl;
    } else std::cout << "The numbers are not equal." << std::endl;
};
/*
    Function that checks if the current Pound is greater than or less than the compared object
    Pre:    other - the other Currency to to be compared
    Post:   prints a statement whether the current Currency object greater or less than moneyWhole and moneyFraction variables from the compared object
    Return: None
*/
void Pound::isGreater(const Currency& other) {
    if (other.getMoneyWhole() > moneyWhole || other.getMoneyWhole() == moneyWhole && other.getMoneyFraction() >= moneyFraction){
        std::cout << "Pound stored in the array is less than/equal to the compared pound." << std::endl;
    }
    else std::cout << "Pound stored in the array is greater than the compared pound." << std::endl;
};
/*
    Function that processes cash and object type inputted and creates a pointer to an object based on that input, then calls the add/subtract functions.
    Pre:    operation - char which stores the instruction (either 'a' for addition or 's' for subtraction)
            cash - double of the amount of cash of the object the user wants to add or subtract
            objType - string of the type of object the user wants to add (either "dollar" or "pound")
    Post:   Changes the current object's moneyWhole and moneyFraction values and prints the resulting values of the class after the addition/subtraction operation
    Return: None
*/
void Pound::OperateInstructionInDerived(char operation, double cash, std::string objType) {
    if (operation == 'a') {
        Pound* p = new Pound(cash, objType);
        add(*p);
        delete p;
        print();
    }
    else if (operation == 's') {
        Pound* p = new Pound(cash, objType);
        subtract(*p);
        delete p;
        print();
    }
}
/*
    Function that prints the value of the pound object
    Pre:    None
    Post:   Prints moneyWhole, moneyFraction, and currencyName in the format xx.xx [currencyName] to console
    Return: None
*/
void Pound::print() const {
    std::cout << getMoneyWhole() << "." << getMoneyFraction() << " " << currencyName << std::endl;
}
    
#endif // POUND_H