/*
* Noah Rothgaber
* Battle Kombat
*/

// A player has a name, a number, and a reference to an abstract hero, (which means it can be any type of derived hero)

#ifndef NOAHROTHGABER00303181CPPPROJECT3_PLAYER_H
#define NOAHROTHGABER00303181CPPPROJECT3_PLAYER_H
#include "AbstractKharacter.h"

class Player
{
public:
    AbstractKharacter *playerKharacter;
    int kharacterType = -1;
    int indexOfKharacter = -1;
    std::string playerName;
    int playerNumber;
public:
    Player(int playerNumber) // SET THE PLAYER'S NAME TO THE CORRECT NUMBER
    {
        playerKharacter = nullptr;
        playerName = "Player " + std::to_string(playerNumber);
        this->playerNumber = playerNumber - 1;
        // Since the player kharacter array starts at 0, this controls index
        // but when it's passed into the constructor its representing players starting at 1
    }
};


#endif //NOAHROTHGABER00303181CPPPROJECT3_PLAYER_H
