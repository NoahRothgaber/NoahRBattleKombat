/*
* Noah Rothgaber
* Battle Kombat
*/

#include "ShieldItem.h"
ShieldItem::ShieldItem() // Shield improves defense, but decreases strength and stamina
{
    buff = 6; // Agility
    debuff = -3; // Strength
    cost = -4; // stamina
}

void ShieldItem::affectStats(double *strength, double *agility, double *stamina)
{
    *strength += debuff;
    *agility += buff;
    *stamina += cost;
}