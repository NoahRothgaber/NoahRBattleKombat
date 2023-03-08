/*
* Noah Rothgaber
* Battle Kombat
*/

#include "SwordItem.h"
SwordItem::SwordItem() // a sword item buffs strength, but decreases agility and stamina
{
    buff = 5; // Strength
    debuff = -2; // Agility
    cost = -4; // stamina
}

void SwordItem::affectStats(double *strength, double *agility, double *stamina)
{
    *strength += debuff;
    *agility += buff;
    *stamina += cost;
}