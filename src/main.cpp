#include "core.h"

#include <type_traits>
#include <typeinfo>

using namespace CreatureAdventures;

void print_creature_stats(const Creature& creature)
{
    DEBUG_OUT(std::setw(8));
    DEBUG_OUT(creature.uid << std::setw(20));
    DEBUG_OUT(Creature::tierNames[creature.tier] << std::setw(8));
    DEBUG_OUT(creature.baseAttack << std::setw(4));
    DEBUG_OUT(creature.baseDefense << std::setw(4));
    DEBUG_OUT(creature.baseMaxHP << '\n');
}

void print_item_stats(const Item& item)
{
    DEBUG_OUT(std::setw(8));
    DEBUG_OUT(item.uid << std::setw(20));
    DEBUG_OUT("typeIndex:" << std::setw(4));
    DEBUG_OUT(item.type << std::setw(12));
    DEBUG_OUT(Item::tierNames[item.tier] << std::setw(8));
    DEBUG_OUT(item.uid << std::setw(12));
    DEBUG_OUT(item.name() << std::setw(60));
    DEBUG_OUT(item.description() << std::setw(12));
    DEBUG_OUT("uid:" << std::setw(4));
    DEBUG_OUT((item.persistent ? " is" : " is not") << " persistent\n");
}

int main(int argc, char** argv)
{

    DeckBuilder builder;

    Deck<Creature> creatureDeck = builder.create_creature_deck(50, 30.0);
    creatureDeck.shuffle();

    Deck<Item> itemDeck = builder.create_item_deck(100, 30.0f);
    itemDeck.shuffle();

    Creature creature1(creatureDeck.draw());
    Creature creature2(creatureDeck.draw());

    print_creature_stats(creature1);
    print_creature_stats(creature2);
    DEBUG_OUT("\n\n");

    while ((creature1.get_hp() > 0) && (creature2.get_hp() > 0))
    {
        Action action1(STRIKE, &creature1, &creature2);
        Action action2(STRIKE, &creature2, &creature1);
        
        action1.process();
        action2.process();

        action1.evaded = action2.evasive;
        action2.evasive = action1.evaded;

        action1.apply();
        action2.apply();
        
        DEBUG_OUT("uid " << creature1.uid << " hp: " << creature1.get_hp());
        DEBUG_OUT("\nuid " << creature2.uid << " hp: " << creature2.get_hp() << "\n");
    }

    if (!creature1.get_hp() && !creature2.get_hp())
    {
        DEBUG_OUT("\nTIE!\n");
    }
    else
    {
        DEBUG_OUT('\n' << (creature1.get_hp() > 0 ? creature1.uid : creature2.uid) << " WINS!\n");
    }

    return 0;

}
