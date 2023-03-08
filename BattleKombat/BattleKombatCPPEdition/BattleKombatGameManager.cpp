//
// Created by Noah on 3/7/2023.
//

/*
* Noah Rothgaber
* Battle Kombat
*/
#include <iostream>
#include "BattleKombatGameManager.h"
#include <vector>
#include <algorithm>
#include <random>


void BattleKombatGameManager::welcomeToOutworld() // Intro Screen
{
    std::cout << "Welcome to Outworld mortal fools! I am Shang Tsung, and this is my island. You are gathered here"
                 " for the 450th Mortal Kombat tournament. You will take turns fighting your assigned opponent. "
                 "Do not expect a fair fight, as the fate of Outworld's invasion of EarthRealm is at stake.\n";
}

void BattleKombatGameManager::run() // Main function of the class, runs the games core
{
    int playerTotal = 4; // number of player objects created
    welcomeToOutworld();
    for(int k = 0; k < playerTotal; k++) // start a four player game
    {
        Player temp(k + 1);
        playerKharacters.push_back(temp);
    }

    // This loop ended up working fine, but a similar loop later had to be rewritten
    for(int i = 0 ; i < kharacterNames.size(); i++)
    {
        switch(i)
        {
            case 0: // cage
            case 2: // reptile
            case 7: // sonya
            case 8: // rain
                komboKharacterList.push_back(generateKomboKharacter(i));
                break;

            case 1:
            case 4:
                itemKharacterList.push_back(generateItemKharacter(i));
                break;

            default: // defense jax, kung lao, raiden, jade, kenshi
                defensiveKharacterList.push_back(generateDefensiveKharacter(i));
                break;
        }
    }
    int winnerA = mainGameSwitch(0,1);
    int winnerB = mainGameSwitch(2,3);
    if(winnerA == -1 && winnerB == -1) // in an event of a tie from both matches
    {
        std::cout << "The souls of the dead are mine, I am now strong enough to invade earthrealm myself.\nGAME OVER\n";
    }
    else if(winnerA == -1) // in the event of a tie between match 1
    {
        std::cout << "The winner is " + playerKharacters[winnerB].playerName << " as " <<
                  playerKharacters[winnerB].playerKharacter->getName();
    }
    else if(winnerB == -1)
    {
        std::cout << "The winner is " + playerKharacters[winnerA].playerName << " as " <<
                  playerKharacters[winnerA].playerKharacter->getName();
    }
    else // final round
    {
        std::cout << "FINAL ROUND\n" + playerKharacters[winnerA].playerName + "\tVS\t"
                     + playerKharacters[winnerB].playerName << std::endl << std::endl;
        int finalWinner = fight(winnerA, winnerB);
        if(finalWinner == -1)
        {
            std::cout << "The souls of the dead are mine, "
                         "I am now strong enough to invade earthrealm myself.\nGAME OVER\n";
        }
        else
        {
            std::cout << "The winner is " + playerKharacters[finalWinner].playerName << " as " <<
                      playerKharacters[finalWinner].playerKharacter->getName();
        }
    }
}

// This is player input for the main menu, it can be bypassed by the fight function once kharacters had been selected
// I was pretty proud at the end to see that I actually just made like a real character select screen
int BattleKombatGameManager::mainGameSwitch(int playerAIndex, int playerBIndex)
{
    int winner = -1; // winner boolean
    bool checkedKharacters = false;
    bool gameOver = false;
    int menuSelection = -1;
    int kharacterSelection = -1;
    int totalNumberOfPlayers = 0; // increases to 2 when players lock in.
    while (!gameOver) // End the switch when the game ends
    {
        if(totalNumberOfPlayers == 0) // set up for player 1's turn
        {
            currentPlayer = playerAIndex;
        }
        else // set up for player 2's turn
        {
            currentPlayer = playerBIndex;
        }
        if (totalNumberOfPlayers == 2) // both players locked in, start fight
        {
            menuSelection = 1;
        }
        else // prompt current player
        {
            while (menuSelection < 1 || menuSelection > 5) // inputting chars will crash
            {
                std::cout << playerKharacters[currentPlayer].playerName << "\nYou have the following choices on my "
                                                                           "island.\n[1]\tFight(Lock In)\n[2]\t"
                                                                           "Choose A Kharacter\n[3]\t"
                                                                           "View Current Kharacter Description\n"
                                                                           "[4]\tView Instructions\n[5]\tQuit\n";
                std::cin >> menuSelection;
            }
        }
        switch (menuSelection)
        {
            case 1:
                if (totalNumberOfPlayers == 2) // both players locked in
                {
                    winner = fight(playerAIndex, playerBIndex);
                    gameOver = true; // game over gg
                    totalNumberOfPlayers = 0; // set up for next match
                }

                else if (!checkedKharacters) // if player chooses fight without locking in
                {
                    std::cout << "You don't currently have a character selected.\n";
                }

                else // player 1 locked in
                {
                    checkedKharacters = false;
                    totalNumberOfPlayers++;
                    currentPlayer++;
                }
                break;

            case 2: // Choose your Kharacter!
                checkedKharacters = true;
                selectKharacter(&kharacterSelection); // sends reference of user's kharacter selection
                break;

            case 3:
                printKharacterStats(checkedKharacters); // takes boolean to decline checking stats if no khar chosen
                break;

            case 4: // instructions
                std::cout << "This is Mortal Kombat Tournament held for 4 Players. There are two rounds\n"
                             "Player 1\tvs\tPlayer 2\n\n"
                             "Followed by\n"
                             "Player 3\tvs\tPlayer 4\n\n"
                             "And finally the winners face off with eachother\n\n"
                             "You have three options during your turn; Attack, Defend, and Rest\n"
                             "Attack:\tAttacking costs Stamina, does set damage to your opponent\n"
                             "Defend:\tDefending costs Stamina, mitigates some damage from your opponent\n"
                             "Rest:\tRegenerates Stamina, Regains some Health\n\n"
                             "There are three types of Fighters\n"
                             "Kombo:\tKombo Kharacters deal more damage, but have worse defense.\n"
                             "Defensive: Defensive Kharacters mitigate more damage, but deal less\n"
                             "Item:\tItem Kharacters have their stats affected by items\n\n";
                break;

            case 5: // Quit
                std::cout << "Shall you return to my Island for the next Mortal Kombat tournament, I will be ready.\n";
                gameOver = true;
        }
        menuSelection = -1; // reset menu select

    }
    return winner; // return winner of game.
}

int BattleKombatGameManager::fight(int playerAIndex, int playerBIndex) // main kombat or "battle"
{
    int winner = -1;
    bool player1Healthy = true;
    bool player2Healthy = true;
    int currentTurn = 1; // player 1 starts everytime, could easily have them swap each game
    auto player1Khar = playerKharacters[playerAIndex].playerKharacter;
    auto player2Khar = playerKharacters[playerBIndex].playerKharacter;
    int fightingSelection = -1;
    // I went with assignment of damage so kharacters would deal damage at the same time
    double player1AssignedDamage = 0;
    double player2AssignedDamage = 0;
    while(player1Healthy && player2Healthy)
    {
        if(player1Khar->getStamina() < 0) // reset stamina values if negative
        {
            player1Khar->setStamina(0);
        }
        if(player2Khar->getStamina() < 0)
        {
            player2Khar->setStamina(0);
        }

        std::cout << playerKharacters[playerAIndex].playerName
                  << "\n" <<  player1Khar->getName() << "\nCurrent Health\n" <<
                  player1Khar->getHealth() << "\nCurrent Stamina\n"
                  << player1Khar->getStamina() << "\n\n";

        std::cout << playerKharacters[playerBIndex].playerName << "\n"
                  << player2Khar->getName() << "\nCurrent Health\n"
                  << player2Khar->getHealth() << "\nCurrent Stamina\n"
                  << player2Khar->getStamina() << "\n\n";

        // printing kharacter health and stamina each turn

        for(int i = 0; i < 2; i++) // who's turn is it anyway?
        {
            if(currentTurn == 1)
            {
                std::cout << playerKharacters[playerAIndex].playerName << "\n";
            }
            else
            {
                std::cout << playerKharacters[playerBIndex].playerName << "\n";
            }

            fightPrompt();
            std::cin >> fightingSelection;
            switch(fightingSelection)
            {
                case 1: // This is split between turns, the switch is roughly the same, just which object is different
                    if(currentTurn == 1)
                    {
                        if(player1Khar->getStamina() >= player1Khar->getAttackCost())
                        {
                            // IF player doesn't have enough stamina, I elected to force rest as opposed to
                            // allowing the player to pick two impossible options and force them to choose

                            // updating damage assignment, damage is not guaranteed to be done due to defending
                            player2AssignedDamage += player1Khar->attack();
                        }
                        else
                        {
                            std::cout << "You ran out of stamina! You're forced to rest.\n";
                            player1Khar->rest();
                        }
                    }
                    else // Player 2 attack
                    {
                        if(player2Khar->getStamina() >= player2Khar->getAttackCost())
                        {
                            player1AssignedDamage += player2Khar->attack();
                        }
                        else
                        {
                            std::cout << "You ran out of stamina! You're forced to rest.\n";
                            player2Khar->rest();
                        }
                    }
                    break;

                case 2: // Defend
                    if(currentTurn == 1)
                    {
                        if(player1Khar->getStamina() >= player1Khar->getDefendCost())
                        {
                            player1AssignedDamage -= player1Khar->defend();
                            // decrease the assigned damage this value can be negative to fully mitigate damage
                        }
                        else
                        {
                            std::cout << "You ran out of stamina! You're forced to rest.";
                            player1Khar->rest();
                        }
                    }
                    else // player 2 defend
                    {
                        if(player2Khar->getStamina() >= player2Khar->getDefendCost())
                        {
                            player2AssignedDamage -= player2Khar->defend();
                        }
                        else
                        {
                            std::cout << "You ran out of stamina! You're forced to rest.";
                            player2Khar->rest();
                        }
                    }
                    break;

                case 3: // Rest
                    if(currentTurn == 1)
                    {
                        player1Khar->rest();
                    }
                    else
                    {
                        player2Khar->rest();
                    }
                    break;
            }
            if(currentTurn == 1) // swap whose turn it is
            {
                currentTurn = 2;
            }
            else
            {
                currentTurn = 1;
            }
        }
        if(player1AssignedDamage >= 0 && player2AssignedDamage >= 0)
            // This code will only assign damage if there's damage to assign
        {
            player1Khar->setHealth(player1Khar->getHealth() - player1AssignedDamage);
            player2Khar->setHealth(player2Khar->getHealth() - player2AssignedDamage);
        }
        if(player1Khar->getHealth() <= 0 && player2Khar->getHealth() <= 0) // tie match
        {
            // set health to 0 to ensure damage reads properly
            player1Khar->setHealth(0);
            player2Khar->setHealth(0);
            player1Healthy = false;
            player2Healthy = false;
            std::cout << "Great, both warriors are dead, I suppose it's a wash then.\n";
            std::cout <<  player1Khar->getName() << "\nCurrent Health\n" <<
                      player1Khar->getHealth() << "\nCurrent Stamina\n"
                      << player1Khar->getStamina() << "\n\n";
            std::cout << player2Khar->getName() << "\nCurrent Health\n"
                      << player2Khar->getHealth() << "\nCurrent Stamina\n"
                      << player2Khar->getStamina() << "\n\n";
        }
        else if(player1Khar->getHealth() <= 0) // Player 2 wins
        {
            player1Khar->setHealth(0);
            player1Healthy = false;
            std::cout << "PLAYER 2 WINS\n";
            std::cout <<  player1Khar->getName() << "\nCurrent Health\n" <<
                      player1Khar->getHealth() << "\nCurrent Stamina\n"
                      << player1Khar->getStamina() << "\n\n";
            std::cout << player2Khar->getName() << "\nCurrent Health\n"
                      << player2Khar->getHealth() << "\nCurrent Stamina\n"
                      << player2Khar->getStamina() << "\n\n";
            winner = playerBIndex;
        }
        else if(player2Khar->getHealth() <= 0) // Player 1 wins
        {
            player2Khar->setHealth(0);
            player2Healthy = false;
            std::cout << "PLAYER 1 WINS\n";
            std::cout  << playerKharacters[playerAIndex].playerName << "\n" <<
                       player1Khar->getName() << "\nCurrent Health\n" <<
                       player1Khar->getHealth() << "\nCurrent Stamina\n"
                       << player1Khar->getStamina() << "\n\n";

            std::cout << playerKharacters[playerBIndex].playerName << "\n"
                      << player2Khar->getName() << "\nCurrent Health\n"
                      << player2Khar->getHealth() << "\nCurrent Stamina\n"
                      << player2Khar->getStamina() << "\n\n";
            winner = playerAIndex;
        }
        // zero out assigned damage for next matchup
        player1AssignedDamage = 0;
        player2AssignedDamage = 0;
    }
    // reset the characters for the next match
    player1Khar->reset();
    player2Khar->reset();
    return winner;

}

std::string BattleKombatGameManager::kharacterNameReturn()
{
    std::random_device generator; // creates device used to create random num
    std::uniform_int_distribution<int> distribution(0,10); // creates range or distribution for randomness
    int randNum = distribution(generator); // sets randNum to a rand num using the device and the range
    return kharacterNames[randNum];
}

std::string BattleKombatGameManager::kharacterNameReturn(int who) // return any name
{
    return kharacterNames[who];
    /*
    * 0"Johnny Cage",
    * 1"Cyrax",
    * 2"Reptile",
    * 3"Jax",
    * 4"Kung Lao",
    * 5"Raiden",
    * 6"Jade",
    * 7"Sonya",
    * 8"Rain",
    * 9"Kenshi",
    */
}

KomboKharacter BattleKombatGameManager:: generateRandomKharacter()
{
    double statsArray[4];
    BattleKombatGameManager::generateStats(statsArray, 1);
    KomboKharacter randomKharacter(BattleKombatGameManager::kharacterNameReturn(),
                                   100 + statsArray[0] , statsArray[2],50 + statsArray[1],statsArray[3]);
    return randomKharacter;
}

KomboKharacter BattleKombatGameManager:: generateKomboKharacter(int who)
{
    // these are all the same, just different kharacter types
    // Uses an array that goes through the random device and assigns stats to the kharacter
    // The type of kharacter also modifies the stats
    double statsArray[4];
    BattleKombatGameManager::generateStats(statsArray, 0);
    auto *kharacter = new KomboKharacter(kharacterNameReturn(who), 100 + statsArray[0], statsArray[2],
                                         50 + statsArray[1], statsArray[3]);
    return *kharacter;
}

DefensiveKharacter BattleKombatGameManager::generateDefensiveKharacter(int who)
{
    double statsArray[4];
    BattleKombatGameManager::generateStats(statsArray, 1);
    auto *kharacter = new DefensiveKharacter(kharacterNameReturn(who), 100 + statsArray[0], statsArray[2],
                                             50 + statsArray[1], statsArray[3]);
    return *kharacter;
}

ItemKharacter BattleKombatGameManager::generateItemKharacter(int who)
{
    double statsArray[4];
    BattleKombatGameManager::generateStats(statsArray, 2);
    auto *kharacter = new ItemKharacter(kharacterNameReturn(who), 100 + statsArray[0], statsArray[2],
                                        50 + statsArray[1], statsArray[3]);
    return *kharacter;
}

void BattleKombatGameManager::generateStats(double* stats, int statModify)
{
    int statChange[4]; // health, stamina, strength, agility
    switch(statModify)
    {
        case 0:
            statChange[0] = -2;
            statChange[1] = -6;
            statChange[2] = 10;
            statChange[3] = 0;
            // Kombo Kharacter
            break;

        case 1:
            statChange[0] = 2;
            statChange[1] = 0;
            statChange[2] = -3;
            statChange[3] = 8;
            // Defensive
        case 2:
            statChange[0] = 0;
            statChange[1] = 0;
            statChange[2] = 1;
            statChange[3] = 1;
            // Item

    }

    std::random_device generator; // creates device used to create random num
    std::uniform_int_distribution<int> distribution(10,20); // creates range or distribution for randomness
    int randNumAgil1 = distribution(generator); // sets randNum to a rand num using the device and the range
    int randNumAgil2 = distribution(generator); // sets randNum to a rand num using the device and the range
    int randNumStren1 = distribution(generator); // sets randNum to a rand num using the device and the range
    int randNumStren2 = distribution(generator); // sets randNum to a rand num using the device and the range
    *(stats + 3) = (int) fmax(randNumAgil1, randNumAgil2) + statChange[3];
    *(stats + 2) = (int) fmax(randNumStren1, randNumStren2) + statChange[2];
    // sets the proper stat (using pointer notation) to the max between the two random values
}

void BattleKombatGameManager::selectKharacter(int* kharacterSelection)
{
    while (*kharacterSelection > 9 || *kharacterSelection < 0)
    {
        displayKharacterSelectScreen();
        std::cin >> *kharacterSelection;
    }
    auto playKharPtr = &playerKharacters[currentPlayer].playerKharacter;
    // Changing Cyrax and Kung Lao to item kharacters killed my beautiful loop based referencing :(
    switch(*kharacterSelection)
    {
        // These kharacters are stored all over the place, it used to be a nice order
        case 0: // cage
            *playKharPtr = &komboKharacterList[0];
            break;

        case 1: // Cyrax
            *playKharPtr = &itemKharacterList[0];
            break;

        case 2:
            *playKharPtr = &komboKharacterList[1];
            break;// Reptile

        case 3:// Jax
            *playKharPtr = &defensiveKharacterList[0];
            break;

        case 4:   // Kung Lao
            *playKharPtr = &itemKharacterList[1];
            break;

        case 5: // Raiden
            *playKharPtr = &defensiveKharacterList[1];
            break;

        case 6: // Jade
            *playKharPtr = &defensiveKharacterList[2];
            break;

        case 7: // Sonya
            *playKharPtr = &komboKharacterList[2];
            break;

        case 8: // Rain
            *playKharPtr = &komboKharacterList[3];
            break;

        case 9: // Kenshi
            *playKharPtr = &defensiveKharacterList[3];
            break;
    }
    *kharacterSelection = -1;
}

void BattleKombatGameManager::printKharacterStats(bool checkedKharacters)
// This code was also massacred by the item kharacter disaster
{
    if (checkedKharacters) // can only print the stats of a kharacter if you have one
    {
        auto temp = playerKharacters[currentPlayer].playerKharacter; // pointer for simplification
        for(int i = 0; i < komboKharacterList.size(); i++)
        {

            if (komboKharacterList[i].getName() == temp->getName()) // vectors  with the even (4) amount of khar
            {
                std::cout << komboKharacterList[i];
            }
            if (defensiveKharacterList[i].getName() == temp->getName())
            {
                std::cout << defensiveKharacterList[i];
            }
        }
        // wouuld look better if I added two more item kharacters
        if(temp->getName() == "Cyrax")
        {
            std::cout << itemKharacterList[0];
        }
        else if(temp->getName() == "Kung Lao")
        {
            std::cout << itemKharacterList[1];
        }
    }
}

void BattleKombatGameManager::displayKharacterSelectScreen()
{
    // I DID NOT BUILD THIS, I used the following website
    // https://textkool.com/en/ascii-art-generator?hl=default&vl=default&font=Red%20Phoenix&text=Your%20text%20here%20
    std::cout << "   ###                     #                                       #####                       \n"
                 "  #   #                    #  ####  #    # #    # #    # #   #    #     #   ##    ####  ###### \n"
                 " #     #                   # #    # #    # ##   # ##   #  # #     #        #  #  #    # #      \n"
                 " #     #                   # #    # ###### # #  # # #  #   #      #       #    # #      #####  \n"
                 " #     #             #     # #    # #    # #  # # #  # #   #      #       ###### #  ### #      \n"
                 "  #   #              #     # #    # #    # #   ## #   ##   #      #     # #    # #    # #      \n"
                 "   ###                #####   ####  #    # #    # #    #   #       #####  #    #  ####  ###### \n"
                 "                                                                                               \n"
                 "   #                #####                                                                      \n"
                 "  ##               #     # #   # #####    ##   #    #                                          \n"
                 " # #               #        # #  #    #  #  #   #  #                                           \n"
                 "   #               #         #   #    # #    #   ##                                            \n"
                 "   #               #         #   #####  ######   ##                                            \n"
                 "   #               #     #   #   #   #  #    #  #  #                                           \n"
                 " #####              #####    #   #    # #    # #    #                                          \n"
                 "                                                                                               \n"
                 "  #####              ######                                                                    \n"
                 " #     #             #     # ###### #####  ##### # #      ######                               \n"
                 "       #             #     # #      #    #   #   # #      #                                    \n"
                 "  #####              ######  #####  #    #   #   # #      #####                                \n"
                 " #                   #   #   #      #####    #   # #      #                                    \n"
                 " #                   #    #  #      #        #   # #      #                                    \n"
                 " #######             #     # ###### #        #   # ###### ######                               \n"
                 "                                                                                               \n"
                 "  #####                    #                                                                   \n"
                 " #     #                   #   ##   #    #                                                     \n"
                 "       #                   #  #  #   #  #                                                      \n"
                 "  #####                    # #    #   ##                                                       \n"
                 "       #             #     # ######   ##                                                       \n"
                 " #     #             #     # #    #  #  #                                                      \n"
                 "  #####               #####  #    # #    #                                                     \n"
                 "                                                                                               \n"
                 " #                   #    #                         #                                          \n"
                 " #    #              #   #  #    # #    #  ####     #         ##    ####                       \n"
                 " #    #              #  #   #    # ##   # #    #    #        #  #  #    #                      \n"
                 " #    #              ###    #    # # #  # #         #       #    # #    #                      \n"
                 " #######             #  #   #    # #  # # #  ###    #       ###### #    #                      \n"
                 "      #              #   #  #    # #   ## #    #    #       #    # #    #                      \n"
                 "      #              #    #  ####  #    #  ####     ####### #    #  ####                       \n"
                 "                                                                                               \n"
                 " #######             ######                                                                    \n"
                 " #                   #     #   ##   # #####  ###### #    #                                     \n"
                 " #                   #     #  #  #  # #    # #      ##   #                                     \n"
                 " ######              ######  #    # # #    # #####  # #  #                                     \n"
                 "       #             #   #   ###### # #    # #      #  # #                                     \n"
                 " #     #             #    #  #    # # #    # #      #   ##                                     \n"
                 "  #####              #     # #    # # #####  ###### #    #                                     \n"
                 "                                                                                               \n"
                 "  #####                    #                                                                   \n"
                 " #     #                   #   ##   #####  ######                                              \n"
                 " #                         #  #  #  #    # #                                                   \n"
                 " ######                    # #    # #    # #####                                               \n"
                 " #     #             #     # ###### #    # #                                                   \n"
                 " #     #             #     # #    # #    # #                                                   \n"
                 "  #####               #####  #    # #####  ######                                              \n"
                 "                                                                                               \n"
                 " #######              #####                                                                    \n"
                 " #    #              #     #  ####  #    # #   #   ##                                          \n"
                 "     #               #       #    # ##   #  # #   #  #                                         \n"
                 "    #                 #####  #    # # #  #   #   #    #                                        \n"
                 "   #                       # #    # #  # #   #   ######                                        \n"
                 "   #                 #     # #    # #   ##   #   #    #                                        \n"
                 "   #                  #####   ####  #    #   #   #    #                                        \n"
                 "                                                                                               \n"
                 "  #####              ######                                                                    \n"
                 " #     #             #     #   ##   # #    #                                                   \n"
                 " #     #             #     #  #  #  # ##   #                                                   \n"
                 "  #####              ######  #    # # # #  #                                                   \n"
                 " #     #             #   #   ###### # #  # #                                                   \n"
                 " #     #             #    #  #    # # #   ##                                                   \n"
                 "  #####              #     # #    # # #    #                                                   \n"
                 "                                                                                               \n"
                 "  #####              #    #                                                                    \n"
                 " #     #             #   #  ###### #    #  ####  #    # #                                      \n"
                 " #     #             #  #   #      ##   # #      #    # #                                      \n"
                 "  ######             ###    #####  # #  #  ####  ###### #                                      \n"
                 "       #             #  #   #      #  # #      # #    # #                                      \n"
                 " #     #             #   #  #      #   ## #    # #    # #                                      \n"
                 "  #####              #    # ###### #    #  ####  #    # #                                      \n"
                 "                                                                                               \n";
    std::cout << " ######                                        #####                                          \n"
                 " #     # #      ######   ##    ####  ######   #     # ###### #      ######  ####  #####       \n"
                 " #     # #      #       #  #  #      #        #       #      #      #      #    #   #         \n"
                 " ######  #      #####  #    #  ####  #####     #####  #####  #      #####  #        #         \n"
                 " #       #      #      ######      # #              # #      #      #      #        #         \n"
                 " #       #      #      #    # #    # #        #     # #      #      #      #    #   #         \n"
                 " #       ###### ###### #    #  ####  ######    #####  ###### ###### ######  ####    #         \n"
                 "                                                                                              \n"
                 " #     #                        #    #                                                        \n"
                 "  #   #   ####  #    # #####    #   #  #    #   ##   #####    ##    ####  ##### ###### #####  \n"
                 "   # #   #    # #    # #    #   #  #   #    #  #  #  #    #  #  #  #    #   #   #      #    # \n"
                 "    #    #    # #    # #    #   ###    ###### #    # #    # #    # #        #   #####  #    # \n"
                 "    #    #    # #    # #####    #  #   #    # ###### #####  ###### #        #   #      #####  \n"
                 "    #    #    # #    # #   #    #   #  #    # #    # #   #  #    # #    #   #   #      #   #  \n"
                 "    #     ####   ####  #    #   #    # #    # #    # #    # #    #  ####    #   ###### #    # \n"
                 "                                                                                              \n";
}



