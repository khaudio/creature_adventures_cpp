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
    DEBUG_OUT(creature.baseMaxHP << std::setw(10));
    DEBUG_OUT(std::setprecision(2));
    DEBUG_OUT((creature.baseEvasiveness * 100) << " %" << '\n');
}

void print_item_stats(const Item& item)
{
    DEBUG_OUT('\t' << std::setw(5));
    DEBUG_OUT("uid: " << std::setw(4));
    DEBUG_OUT(item.uid << std::setw(10));
    DEBUG_OUT(Item::tierNames[item.tier] << std::setw(8));
    DEBUG_OUT("value: " << std::setw(4) << item.value << std::setw(8));
    DEBUG_OUT(item.name() << std::setw(60));
    DEBUG_OUT(item.description() << std::setw(12));
    DEBUG_OUT((item.persistent ? " is" : " is not") << " persistent\n");
}

void print_creature_pair(const Creature& creature1, const Creature& creature2)
{
    DEBUG_OUT('\n');

    DEBUG_OUT(std::setw(4) << "\tuid " << std::setw(3) << creature1.uid);
    DEBUG_OUT(std::setw(12) << Creature::tierNames[creature1.tier]);
    visualize_creature_hp(creature1, 80);

    DEBUG_OUT(std::setw(4) << "\tuid " << std::setw(3) << creature2.uid);
    DEBUG_OUT(std::setw(12) << Creature::tierNames[creature2.tier]);
    visualize_creature_hp(creature2, 80);

    DEBUG_OUT("\n\n");
}

int main(int argc, char** argv)
{

    while (true)
    {
        DeckBuilder builder;

        Deck<Creature> creatureDeck = builder.create_creature_deck(100, 30.0f);
        Deck<Item> itemDeck = builder.create_item_deck(1000, 30.0f);

        creatureDeck.shuffle();
        itemDeck.shuffle();

        Creature creature1(creatureDeck.draw());
        Creature creature2(creatureDeck.draw());

        /* Force epic creatures */
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
        DEBUG_OUT("hp" << std::setw(12));
        DEBUG_OUT("evasiveness" << "\n\n");

        print_creature_stats(creature1);
        print_creature_stats(creature2);
        DEBUG_OUT("\n");

        char x, replay;

        while ((creature1.get_hp() > 0) && (creature2.get_hp() > 0))
        {
            DEBUG_OUT("\nPress enter to continue or c to cancel...\n\n");
            x = getch();
            if (x == 'c')
            {
                return 0;
            }

            CombatAction action1, action2;
            CombatActionPair combatExchange(&action1, &action2);

            action1.invoker = &creature1;
            action1.target = &creature2;

            action2.invoker = &creature2;
            action2.target = &creature1;

            if (creature1.get_attack() <= creature2.get_defense())
            {
                Item item(itemDeck.draw());
                while (item.type != ELIXIR)
                {
                    item = itemDeck.draw();
                }
                CreatureModifier mod;
                mod.attackOffset += item.value;
                mod.numTurns = 2;
                creature1.add_modifier(mod);
                action1.type = PASS;
                
                DEBUG_OUT(creature1.uid << " drinks elixir for +");
                DEBUG_OUT(item.value << " attack power\n");
            }
            else
            {
                action1.type = STRIKE;
            }

            if (creature2.get_attack() <= creature1.get_defense())
            {
                Item item(itemDeck.draw());
                while (item.type != ELIXIR)
                {
                    item = itemDeck.draw();
                }
                CreatureModifier mod;
                mod.attackOffset += item.value;
                mod.numTurns = 2;
                creature2.add_modifier(mod);
                action2.type = PASS;

                DEBUG_OUT(creature2.uid << " drinks elixir for +");
                DEBUG_OUT(item.value << " attack power\n");
            }
            else
            {
                action2.type = STRIKE;
            }

            combatExchange.execute();

            print_creature_pair(creature1, creature2);
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

        if ((replay != 'r') && (replay != 'R'))
        {
            break;
        }
    }

    return 0;

}
