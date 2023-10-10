#include "core.h"

#include <type_traits>
#include <typeinfo>

using namespace CreatureAdventures;


int main(int argc, char** argv)
{

    DeckBuilder builder;
    Deck<Creature> creatureDeck = builder.create_creature_deck(50, 30.0);

    std::cout << "\n\nCREATURES:\n\n";
    for (const auto& card: creatureDeck)
    {
        std::cout << std::setw(12);
        std::cout << Creature::tierNames[card.tier] << std::setw(8);
        std::cout << card.baseAttack << std::setw(4);
        std::cout << card.baseDefense << std::setw(4);
        std::cout << card.baseMaxHP << '\n';
    }

    // Deck<Item> itemDeck = builder.create_single_item_deck(0, 2, 30.0f);

    std::vector<Item*> itemDeck;
    itemDeck.emplace_back(new Potion(0, 0, 30.0f, false));
    itemDeck.emplace_back(new Poison(1, 1, 40.0f, true));

    std::cout << "\n\nITEMS:\n\n";
    for (auto c: itemDeck)
    {
        auto card = c;

        std::cout << std::setw(12);
        std::cout << typeid(*card).name() << std::setw(20);
        std::cout << "itemTypeIndex:" << std::setw(4);
        std::cout << card->itemTypeIndex << std::setw(12);
        std::cout << Item::tierNames[card->tier] << std::setw(8);
        std::cout << "uid:" << std::setw(4) << card->uid << std::setw(12);
        std::cout << card->name << std::setw(80);
        std::cout << card->description << std::setw(20);
        std::cout << (card->persistent ? "is" : "is not") << " persistent\n";
    }

    for (const auto card: itemDeck) delete card;

    return 0;

}

