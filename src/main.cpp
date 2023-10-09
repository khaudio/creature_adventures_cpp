#include "core.h"
#include "dice.h"

#include <iostream>

int main(int argc, char** argv)
{
    int sides(6);
    std::cout << "dice roll: " << CreatureAdventures::roll_dice(sides);
    std::cout << " of possible " << sides << '\n';
    return 0;
}

