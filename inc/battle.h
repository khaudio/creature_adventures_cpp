#ifndef CREATUREADVENTURES_BATTLE_H
#define CREATUREADVENTURES_BATTLE_H

#include "creature.h"

#include <deque>

namespace CreatureAdventures
{

class Battle
{

protected:

    /* False when aggressor forfeits */
    bool _aggressorActive;

    /* False when defender forfeits */
    bool _defenderActive;

    /* True when battle is a tie */
    bool _isDraw;

    /* Queue of actions to be executed */
    std::deque<Action> _aggressorActionQueue;
    std::deque<Action> _defenderActionQueue;

public:

    /* Creature that initiated the battle */
    Creature* aggressor;

    /* Creature targeted by attacker */
    Creature* defender;

    /* True if both players are human */
    bool pvp;

public:

    Battle();
    Battle(Creature* attackingCreature, Creature* defendingCreature);
    Battle(const Battle& ref);

    ~Battle();

    bool active();

    /* Check victory conditions and return
    the victor if battle is over and not a draw,
    otherwise return nullptr */
    Creature* result();

protected:

    void _switch_creatures(
            Creature* aggressingCreature,
            Creature* defendingCreature
        );

    Action _get_next_action(std::deque<Action>* queue);

public:

    /* Process a single action; in normal pvp play,
    actions should be processed in pairs */
    void process_single_action(Action action, Creature* invoker, Creature* target);

    /* Process actions in pairs so that
    combat happens simultaneously */
    void process_action_pair_from_queue();

};

};

#endif
