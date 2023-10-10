#include "core.h"

#include <iostream>

using namespace CreatureAdventures;

int main(int argc, char** argv)
{
    DeckBuilder builder;
    Deck creatureDeck = builder.create_creature_deck(50, 30.0);

    for (const auto& card: creatureDeck)
    {
        std::cout << Creature::tierNames[card.tier] << '\n';
    }
    
    return 0;
}

