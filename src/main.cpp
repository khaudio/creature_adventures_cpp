#include "core.h"

using namespace CreatureAdventures;

int main(int argc, char** argv)
{
    std::cout << "numTiers: " << TieredObjectBase::numTiers << '\n';
    for (int i(0); i < 5; ++i)
    {
        std::cout << "tierNames: " << TieredObjectBase::tierNames[i] << '\n';
        std::cout << "tierVolumeRatios: " << TieredObjectBase::tierVolumeRatios[i] << '\n';
        std::cout << "tierQualityThresholds: " << TieredObjectBase::tierQualityThresholds[i].first << '\t';
        std::cout << TieredObjectBase::tierQualityThresholds[i].second << "\n\n";
    }

    DeckBuilder builder;
    Deck creatureDeck = builder.create_creature_deck(50, 30.0);

    for (const auto& card: creatureDeck)
    {
        std::cout << std::setw(12);
        std::cout << Creature::tierNames[card.tier] << std::setw(8);
        std::cout << card.baseAttack << std::setw(4);
        std::cout << card.baseDefense << std::setw(4);
        std::cout << card.baseMaxHP << '\n';
    }
    
    return 0;
}

