#include "core.h"

#include <type_traits>
#include <typeinfo>

using namespace CreatureAdventures;

int main(int argc, char** argv)
{

    DeckBuilder builder;
    Deck<Creature> creatureDeck = builder.create_creature_deck(50, 30.0);

    creatureDeck.shuffle();

    std::cout << "\n\nCREATURES:\n\n";
    while (creatureDeck.size())
    {
        Creature card = creatureDeck.draw();
        std::cout << std::setw(12);
        std::cout << Creature::tierNames[card.tier] << std::setw(8);
        std::cout << card.baseAttack << std::setw(4);
        std::cout << card.baseDefense << std::setw(4);
        std::cout << card.baseMaxHP << '\n';
    }

    ItemDeck itemDeck = builder.create_item_deck(100, 30.0f);
    itemDeck.shuffle();

    std::cout << "\n\nITEMS:\n\n";
    while(itemDeck.size())
    {
        Item card = itemDeck.draw();
        std::cout << std::setw(12);
        std::cout << typeid(card).name() << std::setw(20);
        std::cout << "typeIndex:" << std::setw(4);
        std::cout << card.typeIndex << std::setw(12);
        std::cout << Item::tierNames[card.tier] << std::setw(8);
        std::cout << "uid:" << std::setw(4) << card.uid << std::setw(12);
        std::cout << card.name << std::setw(80);
        std::cout << card.description << std::setw(20);
        std::cout << (card.persistent ? "is" : "is not") << " persistent\n";
    }

    return 0;

}

