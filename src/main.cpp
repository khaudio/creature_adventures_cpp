#include "core.h"

#include <type_traits>
#include <typeinfo>

using namespace CreatureAdventures;

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
        DEBUG_OUT(card.name() << std::setw(80));
        DEBUG_OUT(card.description() << std::setw(20));
        DEBUG_OUT("uid:" << std::setw(4));
        DEBUG_OUT((card.persistent ? "is" : "is not") << " persistent\n");
    }

    return 0;

}

