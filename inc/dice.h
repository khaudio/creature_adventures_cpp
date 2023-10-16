#ifndef CREATUREADVENTURES_DICE_H
#define CREATUREADVENTURES_DICE_H

#include <random>

namespace CreatureAdventures
{

/* Returns a random value;
where (min <= result <= max) */
template <typename T>
T random_multiplier_roll(T min = 0.0, T max = 1.0);

};

#endif