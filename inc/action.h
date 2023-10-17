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

    /* enum for which action is to be performed */
    ActionIndex type;

    /* Whether the action is between two players */
    bool pvp;

    /* Values to scale HP by */
    float invokerHPScaler = 0;
    float targetHPScaler = 0;

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

public:

    Action(ActionIndex actionType, bool isPvp);
    Action(const Action& ref);

    ~Action();

protected:

    /* Enforce that the action is of a valid type */
    void _validate_type();

public:

    const char* name() const;
    const char* description() const;

    /* Scales creature's current HP
    by a factor of the provided value */

    void scale_invoker_hp(float value);
    void scale_target_hp(float value);

    /* Offsets creature's HP
    by a fixed value */

    void offset_invoker_hp(float invokerHPOffset);
    void offset_target_hp(float targetHPOffset);

    /* Return values to scale and offset by */

    float get_invoker_scale();
    float get_invoker_offset();

    float get_target_scale();
    float get_target_offset();

};

};

#endif
