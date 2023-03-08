/*
* Noah Rothgaber
* Battle Kombat
*/

#include "KomboKharacter.h"
// My comments for the item kharacter are the same for this class
KomboKharacter::KomboKharacter(std::string n, double maxH, double maxP, double maxS, double maxA)
{
    name= std::move(n);
    strength = maxP;
    agility = maxA;
    health = maxH;
    stamina = maxS;
    maxHealth = maxH;
    maxStamina = maxS;
    attackCost = 7.0;
    defendCost = 8.0;
    originalStrength = strength;
    originalAgility = agility;
    originalHealth = health;
    originalStamina = stamina;
}

KomboKharacter::KomboKharacter()
{
    name = "DUMMY";
    health = 666;
}

KomboKharacter& KomboKharacter::operator=(const KomboKharacter &right)
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
        originalStrength = right.getStrength();
        originalAgility = right.getAgility();
        originalHealth = right.getHealth();
        originalStamina = right.getStamina();
    }
    return *this;
}

KomboKharacter::KomboKharacter(const KomboKharacter &obj)
{
    name= obj.getName();
    strength = obj.getStrength();
    agility = obj.getAgility();
    health = obj.getHealth();
    stamina = obj.getStamina();
    maxHealth = obj.getMaxHealth();
    maxStamina = obj.getMaxStamina();
    originalStrength = obj.getStrength();
    originalAgility = obj.getAgility();
    originalHealth = obj.getHealth();
    originalStamina = obj.getStamina();
}

KomboKharacter:: KomboKharacter(KomboKharacter && temp)
{
        // "Steal" the resource from the temp object
        this->health = temp.health;
        this->stamina = temp.stamina;
        this->strength = temp.strength;
        this->agility = temp.agility;
        this->maxHealth = temp.maxHealth;
        this->maxStamina = temp.maxStamina;
        this->name = temp.name;

    this->originalAgility = temp.originalAgility;
    this->originalStrength = temp.originalStrength;
    this->originalHealth = temp.originalHealth;
    this->originalStamina = temp.originalStamina;

}

KomboKharacter& KomboKharacter::operator=(KomboKharacter&& right)
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

KomboKharacter::~KomboKharacter()
{
    if(health == -20)
    {
        delete this;
    }
}

double KomboKharacter::attack()
{
    stamina -= 7;
    return strength;
}

double KomboKharacter::defend()
{
    stamina -= 8;
    return agility;
}
void KomboKharacter::rest()
{
    stamina += 7;
    health += 2;
}

void KomboKharacter::reset()
{
    health = originalHealth;
    stamina = originalStamina;
    agility = originalAgility;
    strength = originalStrength;
}