/*
* Noah Rothgaber
* Battle Kombat
*/
#ifndef NOAHROTHGABER00303181CPPPROJECT3_ABSTRACTITEM_H
#define NOAHROTHGABER00303181CPPPROJECT3_ABSTRACTITEM_H
#include <iostream>

class AbstractItem
{
public:

    // An item has a name, buff, debuff, and stamina cost to consume. All items are consumed by default giving
    // item kharacters the least amount of base stamina in the game
    std::string name;
    double buff;
    double debuff;
    double cost;
    const std::string getName() const {
        return name;
    }

    void setName(std::string name) {
        name = std::move(name);
    }

    // affect stats applies the buffs, debuffs, and costs
    virtual void affectStats(double *strength, double *agility, double *stamina) = 0;

};


#endif //NOAHROTHGABER00303181CPPPROJECT3_ABSTRACTITEM_H
