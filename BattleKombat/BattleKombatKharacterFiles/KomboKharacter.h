/*
* Noah Rothgaber
* Battle Kombat
*/
#ifndef BATTLECODE_KomboKharacter_H
#define BATTLECODE_KomboKharacter_H

#include <string>
#include "AbstractKharacter.h"
// Kombo Kharacter does more Damage, but it costs more
class KomboKharacter : public AbstractKharacter{
public:
    double attackCost = 7;
    double defendCost = 8;
    double originalStrength;
    double originalAgility;
    double originalHealth;
    double originalStamina;
    KomboKharacter(); // default constructor for dummy characters
    KomboKharacter(std::string n, double maxHealth, double strength, double maxStamina, double agility); // Constructor
    KomboKharacter(const KomboKharacter&); // Copy Constructor
    KomboKharacter& operator=(const KomboKharacter &right); // Copy Assignment Overload
    ~KomboKharacter(); // Destructor I don't use the heap so my destructor is default
    KomboKharacter& operator=(KomboKharacter &&); // Move Assignment Overload
    KomboKharacter(KomboKharacter &&); // Move Constructor

    friend std::ostream& operator << (std::ostream& os, const KomboKharacter& KomboKharacter)
    {
        std::string kharInfo =
                "Kharacter Name\t\t" + KomboKharacter.name + "\nKharacter Role\t\tKombo\n" +
                "Kharacter Health\t" + std::to_string((int)KomboKharacter.health) + "\n"
                + "Kharacter Stamina\t" + std::to_string((int)KomboKharacter.stamina) + "\n" +
                "Kharacter Agility\t" + std::to_string((int)KomboKharacter.agility) + "\n" +
                "Kharacter Strength\t" + std::to_string((int)KomboKharacter.strength) + "\n";
        os << kharInfo;
        return os;
    }
    // https://learn.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170

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

#endif //BATTLECODE_KomboKharacter_H
