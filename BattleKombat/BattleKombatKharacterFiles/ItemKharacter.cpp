/*
* Noah Rothgaber
* Battle Kombat
*/

#include "ItemKharacter.h"
#include "AbstractKharacter.h"
ItemKharacter::ItemKharacter() // in case I need a default item kharacter to fill space
{
    name = "DUMMY";
    health = 666;
}

ItemKharacter::ItemKharacter(std::string n, double maxH, double maxP, double maxS, double maxA)
{
    // constructor with proper stat filling
    name= std::move(n);
    strength = maxP;
    agility = maxA;
    health = maxH;
    stamina = maxS;
    maxHealth = maxH;
    maxStamina = maxS;
    attackCost = 10.0;
    defendCost = 3.0;
    // add items to the item array
    itemVector.push_back(new ArmorItem);
    itemVector.push_back(new ShieldItem);
    itemVector.push_back(new ShieldItem);
    for(auto item : itemVector)
    {
        // consume all items
        consumeItem(item);
    }
    originalStrength = strength;
    originalAgility = agility;
    originalHealth = health;
    originalStamina = stamina;
}

ItemKharacter& ItemKharacter ::operator=(const ItemKharacter &right) // move operator
{
    if(this != &right)
    {
        if(health < 20)
            delete this;
        name = right.getName();
        strength = right.getStrength();
        agility = right.getAgility();
        health = right.getHealth();
        stamina = right.getStamina();
        maxHealth = right.getMaxHealth();
        maxStamina = right.getMaxStamina();
        attackCost = 10.0;
        defendCost = 3.0;
        originalStrength = right.originalStrength;
        originalAgility = right.originalAgility;
        originalHealth = right.originalHealth;
        originalStamina = right.originalStamina;
    }
    return *this;

}

ItemKharacter::ItemKharacter(const ItemKharacter &obj) // copy
{
    name= obj.getName();
    strength = obj.getStrength();
    agility = obj.getAgility();
    health = obj.getHealth();
    stamina = obj.getStamina();
    maxHealth = obj.getMaxHealth();
    maxStamina = obj.getMaxStamina();
    attackCost = 10.0;
    defendCost = 3.0;
    originalStrength = obj.originalStrength;
    originalAgility = obj.originalAgility;
    originalHealth = obj.originalHealth;
    originalStamina = obj.originalStamina;
}

ItemKharacter:: ItemKharacter(ItemKharacter && temp) // move reassignment
{
    // "Steal" the resource from the temp object
    this->health = temp.health;
    this->stamina = temp.stamina;
    this->strength = temp.strength;
    this->agility = temp.agility;
    this->maxHealth = temp.maxHealth;
    this->maxStamina = temp.maxStamina;
    this->name = temp.name;
    this->attackCost = 10.0;
    this->defendCost = 3.0;
    this->originalStrength = temp.originalStrength;
    this->originalAgility = temp.originalAgility;
    this->originalHealth = temp.originalHealth;
    this->originalStamina = temp.originalStamina;
    // Put the temp object in a safe state
    // for its destructor to run
}

ItemKharacter& ItemKharacter::operator=(ItemKharacter&& right) // copy reassignment
{
    if(this != &right)
    {
        std::swap(name, right.name);
        std::swap(strength, right.strength);
        std::swap(agility, right.agility);
        std::swap(health, right.health);
        std::swap(stamina, right.stamina);
        std::swap(maxHealth, right.maxHealth);
        std::swap(maxStamina, right.maxStamina);
    }
    return *this;
}

ItemKharacter::~ItemKharacter() // destructor
{
    if(health == -20)
    {
        delete this;
    }
}

double ItemKharacter::attack()
{
    stamina -= 6;
    return strength;
}

double ItemKharacter::defend()
{
    stamina -= 6;
    return agility;
}
void ItemKharacter::rest()
{
    stamina += 3;
    health += 1;
}
void ItemKharacter::reset()
{
    health = originalHealth;
    stamina = originalStamina;
    agility = originalAgility;
    strength = originalStrength;
}

void ItemKharacter::consumeItem(AbstractItem *item) // affects stats belonging to player
{
    item->affectStats(&strength, &agility, &stamina);
}