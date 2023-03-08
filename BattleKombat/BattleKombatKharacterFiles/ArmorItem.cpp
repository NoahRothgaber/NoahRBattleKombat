/*
* Noah Rothgaber
* Battle Kombat
*/
#include "ArmorItem.h"

ArmorItem::ArmorItem() // armor slightly buffs agility, doesn't affect stamina, and slightly debuffs strength
{
    buff = 4; // Agility
    debuff = -1; // Strength
    cost = 0; // Stamina
}

void ArmorItem::affectStats(double *strength, double *agility, double *stamina)
{
    *strength += debuff;
    *agility += buff;
    *stamina += cost;
}