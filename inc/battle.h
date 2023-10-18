#ifndef CREATUREADVENTURES_BATTLE_H
#define CREATUREADVENTURES_BATTLE_H

#include "creature.h"
#include "action.h"

#include <deque>

namespace CreatureAdventures
{

/* Declarations */
class Battle;

class Battle
{

protected:

    /* False when aggressor forfeits */
    bool _aggressorActive;

    /* False when defender forfeits */
    bool _defenderActive;

    /* True when battle is a tie */
    bool _isDraw;

public:

    /* Creature that initiated the battle */
    Creature* aggressor;

    /* Creature targeted by attacker */
    Creature* defender;

    /* True if both players are human */
    bool pvp;

protected:

    // /* Queue of actions to be executed */
    // std::deque<Action> _aggressorActionQueue;
    // std::deque<Action> _defenderActionQueue;

    Action _lastAggressorAction;
    Action _lastDefenderAction;

public:

    Battle();
    Battle(
            Creature* attackingCreature,
            Creature* defendingCreature,
            bool isPvp
        );
    Battle(const Battle& ref);

    ~Battle();

protected:

    void _validate_action(Action action);

public:

    bool active();

    /* Check victory conditions and return
    the victor if battle is over and not a draw,
    otherwise return nullptr */
    Creature* result();

public:

    void strike(Action action);

    void forfeit(Action action);

    void switch_creatures(Action action);

    void escape(Action action);

// protected:

//     Action _get_next_action(std::deque<Action>* queue);

public:

    /* Process a single action; in normal pvp play,
    actions should be processed in pairs */
    void process_single_action(Action action);

    // /* Process actions in pairs so that
    // combat happens simultaneously */
    // void process_action_pair_from_queue();

};

};

#endif
