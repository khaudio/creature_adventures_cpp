#include "dice.h"

namespace CreatureAdventures
{

Dice::Dice()
{
    std::srand(std::time(nullptr));
}

Dice::~Dice()
{
}

int Dice::roll(int sides)
{
    return (1 + (std::rand() % sides));
}

};
