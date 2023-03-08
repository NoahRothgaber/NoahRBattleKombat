/*
* Noah Rothgaber
* Battle Kombat
*/

#ifndef NOAHROTHGABER00303181CPPPROJECT3_SHIELDITEM_H
#define NOAHROTHGABER00303181CPPPROJECT3_SHIELDITEM_H

#include "AbstractItem.h"

class ShieldItem: public AbstractItem
{
    public:
        ShieldItem();
        void affectStats(double *strength, double *agility, double *stamina);


};


#endif //NOAHROTHGABER00303181CPPPROJECT3_SHIELDITEM_H
