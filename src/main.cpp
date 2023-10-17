#include "core.h"

#include <type_traits>
#include <typeinfo>

using namespace CreatureAdventures;

void illustrate_roll(float roll)
{
    DEBUG_OUT(std::setw(12) << roll << " ");
    int maxLen(80);
    int length(static_cast<int>(roll * static_cast<float>(maxLen)));
    int remaining(maxLen - length);
    for (int j(0); j < maxLen; ++j)
    {
        if ((j == (maxLen - 1)) && roll >= 1.0) DEBUG_OUT("+");
        else if (j <= length) DEBUG_OUT("-");
        else if (j == (maxLen - 1)) DEBUG_OUT("|");
        else if ((length < j) && (j < (maxLen - 1))) DEBUG_OUT(" ");
    }
    DEBUG_OUT('\n');
}

int main(int argc, char** argv)
{

    DeckBuilder builder;
    Deck<Creature> creatureDeck = builder.create_creature_deck(50, 30.0);

    creatureDeck.shuffle();

    DEBUG_OUT("\n\nCREATURES:\n\n");
    while (creatureDeck.size())
    {
        Creature card = creatureDeck.draw();
        DEBUG_OUT(std::setw(12));
        DEBUG_OUT(typeid(card).name() << std::setw(20));
        DEBUG_OUT(Creature::tierNames[card.tier] << std::setw(8));
        DEBUG_OUT(card.baseAttack << std::setw(4));
        DEBUG_OUT(card.baseDefense << std::setw(4));
        DEBUG_OUT(card.baseMaxHP << '\n');
    }

    Deck<Item> itemDeck = builder.create_item_deck(100, 30.0f);
    itemDeck.shuffle();

    DEBUG_OUT("\n\nITEMS:\n\n");
    while(itemDeck.size())
    {
        Item card = itemDeck.draw();

        DEBUG_OUT(std::setw(12));
        DEBUG_OUT(typeid(card).name() << std::setw(20));
        DEBUG_OUT("typeIndex:" << std::setw(4));
        DEBUG_OUT(card.type << std::setw(12));
        DEBUG_OUT(Item::tierNames[card.tier] << std::setw(8));
        DEBUG_OUT(card.uid << std::setw(12));
        DEBUG_OUT(card.name() << std::setw(60));
        DEBUG_OUT(card.description() << std::setw(16));
        DEBUG_OUT("uid:" << std::setw(4));
        DEBUG_OUT((card.persistent ? "is" : "is not") << " persistent\n");
    }

    for (int i(0); i < 10; ++i)
    {
        float multiplier(1.0);
        float roll = (
                random_multiplier_roll<float>(0.0, 1.0)
                * multiplier
            );

        illustrate_roll(roll);
    }

    return 0;

}
