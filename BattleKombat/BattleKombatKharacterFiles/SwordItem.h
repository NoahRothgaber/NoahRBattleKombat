/*
* Noah Rothgaber
* Battle Kombat
*/

#ifndef NOAHROTHGABER00303181CPPPROJECT3_SWORDITEM_H
#define NOAHROTHGABER00303181CPPPROJECT3_SWORDITEM_H

#include "AbstractItem.h"

class SwordItem
{
public:
    double buff;
    double debuff;
    double cost;
    SwordItem();
    void affectStats(double *strength, double *agility, double *stamina);

};


#endif //NOAHROTHGABER00303181CPPPROJECT3_SWORDITEM_H
