#include "core.h"

#include <type_traits>
#include <typeinfo>
#include <conio.h>

using namespace CreatureAdventures;

void visualize_creature_hp(const Creature& creature, int maxLineLen = 80)
{
    float hpRatio(creature.get_hp() / creature.get_max_hp());
    DEBUG_OUT(std::setw(12) << creature.get_hp() << " ");
    int length(static_cast<int>(hpRatio * static_cast<float>(maxLineLen)
        ));
    int remaining(maxLineLen - length);
    for (int j(0); j < maxLineLen; ++j)
    {
        if ((j == (maxLineLen - 1)) && hpRatio >= 1.0) DEBUG_OUT("+");
        else if (j <= length) DEBUG_OUT("-");
        else if (j == (maxLineLen - 1)) DEBUG_OUT("|");
        else if ((length < j) && (j < (maxLineLen - 1))) DEBUG_OUT(" ");
    }
    DEBUG_OUT('\n');
}

void print_creature_stats(const Creature& creature)
{
    DEBUG_OUT('\t' << std::setw(4) << creature.uid << std::setw(15));
    DEBUG_OUT(Creature::tierNames[creature.tier] << std::setw(8));
    DEBUG_OUT(creature.baseAttack << std::setw(4));
    DEBUG_OUT(creature.baseDefense << std::setw(4));
    DEBUG_OUT(creature.baseMaxHP << '\n');
}

void print_item_stats(const Item& item)
{
    DEBUG_OUT('\t' << std::setw(4) << item.uid << std::setw(15));
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
    while (true)
    {
        DeckBuilder builder;

        Deck<Creature> creatureDeck = builder.create_creature_deck(50, 30.0);
        creatureDeck.shuffle();

        Deck<Item> itemDeck = builder.create_item_deck(100, 30.0f);
        itemDeck.shuffle();

        Creature creature1(creatureDeck.draw());
        Creature creature2(creatureDeck.draw());

        /* Force epic creature vs random creature */
        // while (creature1.tier != EPIC)
        // {
        //     creature1 = creatureDeck.draw();
        // }
        // while (creature2.tier != EPIC)
        // {
        //     creature2 = creatureDeck.draw();
        // }

        DEBUG_OUT("\n\t" << std::setw(4));
        DEBUG_OUT("uid" << std::setw(15));
        DEBUG_OUT("tier" << std::setw(8));
        DEBUG_OUT("atk" << std::setw(4));
        DEBUG_OUT("def" << std::setw(4));
        DEBUG_OUT("hp" << "\n\n");

        print_creature_stats(creature1);
        print_creature_stats(creature2);
        DEBUG_OUT("\n");

        char x, replay;

        while ((creature1.get_hp() > 0) && (creature2.get_hp() > 0))
        {
            DEBUG_OUT("\nPress enter to continue...\n\n");
            x = getch();

            Action action1(STRIKE, &creature1, &creature2);
            Action action2(STRIKE, &creature2, &creature1);
            
            action1.process();
            action2.process();

            action1.evaded = action2.evasive;
            action2.evasive = action1.evaded;

            action1.apply();
            action2.apply();
            
            DEBUG_OUT('\n');
            DEBUG_OUT(std::setw(4) << "\tuid " << std::setw(3) << creature1.uid);
            DEBUG_OUT(std::setw(12) << Creature::tierNames[creature1.tier]);
            visualize_creature_hp(creature1);
            DEBUG_OUT(std::setw(4) << "\tuid " << std::setw(3) << creature2.uid);
            DEBUG_OUT(std::setw(12) << Creature::tierNames[creature2.tier]);
            visualize_creature_hp(creature2);
            DEBUG_OUT("\n\n");
        }

        if (!creature1.get_hp() && !creature2.get_hp())
        {
            DEBUG_OUT("\nTIE!\n");
        }
        else
        {
            DEBUG_OUT('\n' << "CREATURE UID ");
            DEBUG_OUT((creature1.get_hp() > 0 ? creature1.uid : creature2.uid));
            DEBUG_OUT(" WINS!\n");
        }

        DEBUG_OUT("\nPress enter to close or r to replay...\n");
        replay = getch();

        if (replay == 'r')
        {
            continue;
        }
        else
        {
            break;
        }
    }

    return 0;

}
