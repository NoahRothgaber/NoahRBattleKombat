/*
* Noah Rothgaber
* Battle Kombat
*/

#ifndef BATTLEKOMBAT_ABSTRACTKHARACTER_H
#define BATTLEKOMBAT_ABSTRACTKHARACTER_H

#include <utility>
#include "string"


// The parent class
class AbstractKharacter {
protected:
    std::string name;
    double stamina;
    double health;
    double strength;
    double agility;
    double maxStamina;
    double maxHealth;


public:
    // I needed to add attack and defense costs to check for required stamina
    virtual double attack() = 0;
    virtual double defend() = 0;
    virtual void rest() = 0;
    virtual void reset() = 0;
    virtual double getAttackCost() = 0;
    virtual double getDefendCost() = 0;

    const std::string getName() const {
        return name;
    }

    void setName(std::string name) {
        name = std::move(name);
    }

    double getStamina() const {
        return stamina;
    }

    void setStamina(double st) {
        stamina = st;
    }

    double getHealth() const {
        return health;
    }

    void setHealth(double h) {
        health = h;
    }

    double getStrength() const {
        return strength;
    }

    void setStrength(double str) {
        strength = str;
    }

    double getAgility() const {
        return agility;
    }

    void setAgility(double ag) {
        agility = ag;
    }

    double getMaxStamina() const {
        return maxStamina;
    }

    void setMaxStamina(double maxStamina) {
        maxStamina = maxStamina;
    }

    double getMaxHealth() const {
        return maxHealth;
    }

    void setMaxHealth(double maxHealth) {
        maxHealth = maxHealth;
    }

};
#endif //BATTLECODE_ABSTRACTHERO_H
