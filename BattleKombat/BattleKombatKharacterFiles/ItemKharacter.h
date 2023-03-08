/*
* Noah Rothgaber
* Battle Kombat
*/

#ifndef NOAHROTHGABER00303181CPPPROJECT3_ITEMKHARACTER_H
#define NOAHROTHGABER00303181CPPPROJECT3_ITEMKHARACTER_H

#include "AbstractKharacter.h"
#include "AbstractItem.h"
#include "ArmorItem.h"
#include "SwordItem.h"
#include "ShieldItem.h"
#include <string>
#include <vector>
class ItemKharacter : public AbstractKharacter
{
    public:
        double attackCost = 7;
        double defendCost = 8;
        double originalStrength;
        double originalAgility;
        double originalHealth;
        double originalStamina;
        std::vector<AbstractItem*> itemVector;

        // Copy, Move, and Destructor
        ItemKharacter(); // default constructor for dummy characters
        ItemKharacter(std::string n, double maxHealth, double strength, double maxStamina, double agility); // Constructor
        ItemKharacter(const ItemKharacter&); // Copy Constructor
        ItemKharacter& operator=(const ItemKharacter &right); // Copy Assignment Overload
        ~ItemKharacter(); // Destructor I don't use the heap so my destructor is default
        ItemKharacter& operator=(ItemKharacter &&); // Move Assignment Overload
        ItemKharacter(ItemKharacter &&); // Move Constructor

        // Output operator overload
        friend std::ostream& operator << (std::ostream& os, const ItemKharacter& ItemKharacter)
        {
            std::string kharInfo =
                    "Kharacter Name\t\t" + ItemKharacter.name + "\nKharacter Role\t\tItem\n" +
                    "Kharacter Health\t" + std::to_string((int)ItemKharacter.health) + "\n"
                    + "Kharacter Stamina\t" + std::to_string((int)ItemKharacter.stamina) + "\n" +
                    "Kharacter Agility\t" + std::to_string((int)ItemKharacter.agility) + "\n" +
                    "Kharacter Strength\t" + std::to_string((int)ItemKharacter.strength) + "\n";
            os << kharInfo;
            return os;
        }
        // https://learn.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170

        // Virutals
        double attack();
        double defend();
        void rest();
        void reset();

        // Class Specific Functions
        double getAttackCost()
        {
            return attackCost;
        }

        double getDefendCost()
        {
            return defendCost;
        }

        void consumeItem(AbstractItem *item);


    };


#endif //NOAHROTHGABER00303181CPPPROJECT3_ITEMKHARACTER_H
