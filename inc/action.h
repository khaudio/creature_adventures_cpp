#ifndef CREATUREADVENTURES_ACTION_H
#define CREATUREADVENTURES_ACTION_H

#include "tieredobjectbase.h"
#include "dice.h"
#include "creature.h"

#include <memory>

namespace CreatureAdventures
{

/* Declarations */
class Action;

/* Actions are taken by creatures to cause
damage or healing during battles.
Some actions may be used outside of battle */

class Action
{

public:

    static constexpr const int numTypes = 10;

    static constexpr const std::array<ActionIndex, Action::numTypes> types = {
            STRIKE,
            MEDITATE,
            BRACE,
            DODGE,
            INNERPEACE,
            SWITCH,
            FORFEIT,
            ESCAPE,
            CATCH,
            PASS,
        };

    static constexpr const std::array<const char*, Action::numTypes> names = {
            "Strike",
            "Meditate",
            "Brace",
            "Dodge",
            "InnerPeace",
            "Switch",
            "Forfeit",
            "Escape",
            "Catch",
            "Pass",
        };

    static constexpr const std::array<const char*, Action::numTypes> descriptions = {
            "Attack an enemy for damage",
            "Chance to increase attack",
            "Chance to increase defense",
            "Chance to evade incoming attack",
            "Heal for half max HP",
            "Switch to another creature",
            "Concede defeat and end the battle",
            "Run from battle",
            "Attempt to catch a wild creature",
            "Forego action",
        };

public:

    /* enum for which action is to be performed */
    ActionIndex type;

    /* Values to scale HP by */
    float invokerHPScaler = 1.0f;
    float targetHPScaler = 1.0f;

    /* Absolute HP offset;
    Can be a positive or negative float value.
    Positive values add HP (heal);
    negative values remove HP (damage)*/
    float invokerHPOffset = 0;
    float targetHPOffset = 0;

    /* Whether invoker successfully completed
    an evasive maneuver */
    bool evasive = false;

    /* Whether invoker failed to make contact
    or whether target evaded */
    bool evaded = false;

    Creature* invoker;
    Creature* target;

    bool applied = false;

public:

    Action(
            ActionIndex actionTypeIndex,
            Creature* invokingCreature,
            Creature* targetedCreature
        );
    Action(const Action& ref);

    ~Action();

protected:

    /* Enforce that the action is of a valid type */
    void _validate_type();

    /* Throw an error if the action has already been applied */
    void _check_applied();

public:

    const char* name() const;
    const char* description() const;

protected:

    /* Return dice roll by invoking creature */
    float _get_roll();

private:

    void _strike();
    void _meditate();
    void _brace();
    void _dodge();
    void _inner_peace();

public:

    /* Run the action and calculate result */
    void process();

    /* Apply result to Creatures */
    void apply();

};

};

#endif
