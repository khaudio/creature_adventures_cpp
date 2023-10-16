#include "dice.h"

namespace CreatureAdventures
{

template <typename T>
T random_multiplier_roll(T min, T max)
{
    std::random_device rd;
    std::uniform_real_distribution<T> dist(min, max);
    return dist(rd);
}

template float random_multiplier_roll(float, float);
template double random_multiplier_roll(double, double);

};
