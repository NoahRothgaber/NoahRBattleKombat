/*
* Noah Rothgaber
* Battle Kombat
*/

#include "DefensiveKharacter.h"
// The defensive kharacter can defend better than anyone, but normally hits like a wet noodle
DefensiveKharacter::DefensiveKharacter()
{
    name = "DUMMY";
    health = 666;
}


DefensiveKharacter::DefensiveKharacter(std::string n, double maxH, double maxP, double maxS, double maxA)
{
    name= std::move(n);
    strength = maxP;
    agility = maxA;
    health = maxH;
    stamina = maxS;
    maxHealth = maxH;
    maxStamina = maxS;
    attackCost = 10.0;
    defendCost = 3.0;
    originalStrength = strength;
    originalAgility = agility;
    originalHealth = health;
    originalStamina = stamina;
}

DefensiveKharacter& DefensiveKharacter::operator=(const DefensiveKharacter &right)
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

DefensiveKharacter::DefensiveKharacter(const DefensiveKharacter &obj)
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

DefensiveKharacter:: DefensiveKharacter(DefensiveKharacter && temp)
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
}

DefensiveKharacter& DefensiveKharacter::operator=(DefensiveKharacter&& right)
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

DefensiveKharacter::~DefensiveKharacter() // I don't destruct anything as it stands now, but would if the game looped.
{
    if(health == -20)
    {
        delete this;
    }
}

double DefensiveKharacter::attack()
{
    stamina -= 10;
    return strength;
}

double DefensiveKharacter::defend()
{
    stamina -= 3;
    return agility;
}
void DefensiveKharacter::rest()
{
    stamina += 5;
    health += 2;
}
void DefensiveKharacter::reset() // had to keep track of the original values to reset kharacters
{
    health = originalHealth;
    stamina = originalStamina;
    agility = originalAgility;
    strength = originalStrength;
}