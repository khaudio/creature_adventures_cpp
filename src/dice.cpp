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

template <typename T>
void visualize_roll(T roll, T min, T max, int maxLineLen)
{
    DEBUG_OUT(std::setw(12) << roll << " ");
    int length(static_cast<int>(roll * static_cast<T>(maxLineLen)));
    int remaining(maxLineLen - length);
    for (int j(0); j < maxLineLen; ++j)
    {
        if ((j == (maxLineLen - 1)) && roll >= 1.0) DEBUG_OUT("+");
        else if (j <= length) DEBUG_OUT("-");
        else if (j == (maxLineLen - 1)) DEBUG_OUT("|");
        else if ((length < j) && (j < (maxLineLen - 1))) DEBUG_OUT(" ");
    }
    DEBUG_OUT('\n');
}

template float random_multiplier_roll(float, float);
template double random_multiplier_roll(double, double);

template void visualize_roll(float, float, float, int);
template void visualize_roll(double, double, double, int);

};
