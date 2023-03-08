/*
* Noah Rothgaber
* Battle Kombat
*/
// https://stackoverflow.com/questions/40714365/using-relative-paths-to-shortcut-in-include-statements-in-c
#include "../BattleKombatKharacterFiles/KomboKharacter.h"
#include "../BattleKombatKharacterFiles/DefensiveKharacter.h"
#include "../BattleKombatKharacterFiles/Player.h"
#include "../BattleKombatKharacterFiles/ItemKharacter.h"
#include <vector>
#ifndef NOAHROTHGABER00303181CPPPROJECT3_BATTLEKOMBATGAMEMANAGER_H
#define NOAHROTHGABER00303181CPPPROJECT3_BATTLEKOMBATGAMEMANAGER_H


class BattleKombatGameManager
{
public:
    void run();
    static void welcomeToOutworld();
    int mainGameSwitch(int playerAIndex, int playerBIndex);
    static void generateStats(double* stats, int statModify);
    void printKharacterStats(bool checkedKharacters);
    int fight(int playerAIndex, int playerBIndex);
    KomboKharacter generateRandomKharacter();
    KomboKharacter generateKomboKharacter(int who);
    DefensiveKharacter generateDefensiveKharacter(int who);
    ItemKharacter generateItemKharacter(int who);
    std::string kharacterNameReturn();
    std::string kharacterNameReturn(int who);
    std::vector<std::string> kharacterNames = {"Johnny Cage", "Cyrax", "Reptile", "Jax", "Kung Lao", "Raiden", "Jade",
                                               "Sonya", "Rain", "Kenshi"};
    std::vector<DefensiveKharacter> defensiveKharacterList = {};
    std::vector<KomboKharacter> komboKharacterList = {};
    std::vector<ItemKharacter> itemKharacterList = {};
    std::vector<Player> playerKharacters = {}; // Player 1 is 0 Player 2 is 1 etc...
    void displayKharacterSelectScreen();
    int currentPlayer = 0;

    static void fightPrompt()
    {
        std::cout << "You are given the following choices for your turn.\n[1]\tAttack\n[2]\tDefend\n[3]\tRest\n";
    }


private:
    void selectKharacter(int* kharacterSelection);

};


#endif //NOAHROTHGABER00303181CPPPROJECT3_BATTLEKOMBATGAMEMANAGER_H
