/*
* Noah Rothgaber
* Battle Kombat
*/

#ifndef NOAHROTHGABER00303181CPPPROJECT3_ARMORITEM_H
#define NOAHROTHGABER00303181CPPPROJECT3_ARMORITEM_H

#include "AbstractItem.h"

class ArmorItem : public AbstractItem
{
    public:
            ArmorItem();
            void affectStats(double *strength, double *agility, double *stamina);

};


#endif //NOAHROTHGABER00303181CPPPROJECT3_ARMORITEM_H
