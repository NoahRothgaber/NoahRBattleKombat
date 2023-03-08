/*
* Noah Rothgaber
* Battle Kombat
*/
#ifndef NOAHROTHGABER00303181CPPPROJECT3_DEFENSIVEKHARACTER_H
#define NOAHROTHGABER00303181CPPPROJECT3_DEFENSIVEKHARACTER_H

#include <iostream>
#include "AbstractKharacter.h"

class DefensiveKharacter : public AbstractKharacter
{
public:
    double attackCost = 10;
    double defendCost = 3;
    double originalStrength;
    double originalAgility;
    double originalHealth;
    double originalStamina;
    DefensiveKharacter(); // default constructor
    DefensiveKharacter(std::string n, double maxHealth, double strength, double maxStamina, double agility); // Constructor
    DefensiveKharacter(const DefensiveKharacter&); // Copy Constructor
    DefensiveKharacter& operator=(const DefensiveKharacter &right); // Copy Assignment Overload
    ~DefensiveKharacter(); // Destructor I don't use the heap so my destructor is default
    DefensiveKharacter& operator=(DefensiveKharacter &&); // Move Assignment Overload
    DefensiveKharacter(DefensiveKharacter &&); // Move Constructor

    friend std::ostream& operator << (std::ostream& os, const DefensiveKharacter& DefensiveKharacter)
    // I should note I overrode the output operator for all kharacter types to display the correct role for their stats
    {
        std::string kharInfo =
                "Kharacter Name\t\t" + DefensiveKharacter.name + "\nKharacter Role\t\tDefensive\n"
                + "Kharacter Health\t" +std::to_string((int)DefensiveKharacter.health) + "\n"
                + "Kharacter Stamina\t" + std::to_string((int)DefensiveKharacter.stamina) + "\n" +
                "Kharacter Agility\t" + std::to_string((int)DefensiveKharacter.agility) + "\n" +
                "Kharacter Strength\t" + std::to_string((int)DefensiveKharacter.strength) + "\n";
        os << kharInfo;
        return os;
    }
    // https://learn.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170

    //Virtual Function Implements
    double attack();
    double defend();
    void rest();
    void reset();
    double getAttackCost()
    {
        return attackCost;
    }
    double getDefendCost()
    {
        return defendCost;
    }
};


#endif //NOAHROTHGABER00303181CPPPROJECT3_DEFENSIVEKHARACTER_H
