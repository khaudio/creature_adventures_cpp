#ifndef CREATUREADVENTURESDICE_H
#define CREATUREADVENTURESDICE_H

#include <random>
#include <ctime>

namespace CreatureAdventures
{

/* Emulates traditional dice roll */

int roll_dice(int sides = 6)
{
    std::srand(std::time(nullptr));
    return (1 + (std::rand() % sides));
}



};

#endif