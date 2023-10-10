#ifndef CREATUREADVENTURES_DICE_H
#define CREATUREADVENTURES_DICE_H

#include <random>
#include <ctime>

namespace CreatureAdventures
{

/* Emulates traditional dice roll */

class Dice
{

public:

    Dice();
    ~Dice();

    int roll(int sides = 6);

};

};

#endif