#ifndef CREATUREADVENTURES_ACTION_H
#define CREATUREADVENTURES_ACTION_H

#include "tieredobjectbase.h"
#include "dice.h"

#include <memory>

namespace CreatureAdventures
{

class Action;

/* Actions are taken by creatures to cause
damage or healing during battles.
Some actions may be used outside of battle */

enum ActionIndex
{
    STRIKE = 0,
    MEDITATE = 1,
    BRACE = 2,
    DODGE = 3,
    INNERPEACE = 4,
    SWITCH = 5,
    FORFEIT = 6,
    ESCAPE = 7,
    CATCH = 8,
    PASS = 9,
};

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

    bool pvp;

    /* enum for which action is to be performed */
    ActionIndex type;

    /* Absolute HP offset result for invoker.
    Can be a positive or negative float value */
    float invokerHPDelta = 0;

    /* Absolute HP offset result for target.
    Can be a positive or negative float value */
    float targetHPDelta = 0;

    /* Did invoker successfully complete an evasive maneuver */
    bool evasive = false;

    /* Did invoker fail to make contact or did target evade */
    bool evaded = false;

public:

    Action(ActionIndex actionType);
    Action(const Action& ref);

    ~Action();

protected:

    /* Enforce that type is valid */
    void _validate_type();

public:

    const char* name() const;
    const char* description() const;

    /* Modifies target creature's HP.
    Positive values add HP (heal),
    negative values remove HP (damage) */
    void offset_target_hp(float targetHPOffset);

    /* Modifies action invoking creature's HP.
    Positive values add HP (heal),
    negative values remove HP (damage) */
    void offset_invoker_hp(float invokerHPOffset);
    
    /* Takes positive value as argument
    and applies it as a negative hp offset
    to target (damage) */
    void damage_target(float targetHPLost);

    /* Takes positive value as argument
    and applies it as a negative hp offset
    to invoker (damage) */
    void damage_invoker(float invokerHPLost);

};

};

#endif
