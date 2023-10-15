#ifndef CREATUREADVENTURES_BATTLE_H
#define CREATUREADVENTURES_BATTLE_H

#include "creature.h"

#include <deque>

namespace CreatureAdventures
{

class Battle
{

protected:

    /* Queue of actions to be executed */
    std::deque<Action> _aggressorActionQueue;
    std::deque<Action> _defenderActionQueue;

public:

    /* Creature that initiated the battle */
    Creature* aggresor;

    /* Creature targeted by attacker */
    Creature* defender;

    /* True if both players are human */
    bool pvp;

public:

    Battle();
    Battle(const Battle& ref);

    ~Battle();

    bool active();

protected:

    void _update_action_queue_creature(
            std::deque<Action>* queue
        );

    void _switch_creatures(
            Creature* aggresingCreature,
            Creature* defendingCreature
        );

    Action _get_next_action(std::deque<Action>* queue);

public:

    /* Process a single action; in normal pvp play,
    actions should be processed in pairs */
    void process_single_action(Action action);

    /* Process actions in pairs so that
    combat happens simultaneously */
    void process_action_pair_from_queue();

};

};

#endif
