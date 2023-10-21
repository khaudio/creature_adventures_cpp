#ifndef CREATUREADVENTURES_ACTION_H
#define CREATUREADVENTURES_ACTION_H

#include "dice.h"
#include "creature.h"
#include "item.h"
#include "player.h"

#include <memory>

namespace CreatureAdventures
{

/* Declarations */
class Action;
class ActionPair;

/* Actions are taken by creatures to cause
damage or healing during battles.
Some actions may be used outside of battle */

class Action
{

public:

    static constexpr const int numTypes = 11;

    static constexpr const std::array<ActionIndex, Action::numTypes> types = {
            STRIKE,
            MEDITATE,
            BRACE,
            DODGE,
            SWITCH,
            FORFEIT,
            ESCAPE,
            CATCH,
            PASS,
            INNERPEACE,
            USEITEM,
        };

    static constexpr const std::array<const char*, Action::numTypes> names = {
            "Strike",
            "Meditate",
            "Brace",
            "Dodge",
            "Switch",
            "Forfeit",
            "Escape",
            "Catch",
            "Pass",
            "Inner Peace",
            "Use Item"
        };

    static constexpr const std::array<const char*, Action::numTypes> descriptions = {
            "Attack an enemy for damage",
            "Chance to increase attack",
            "Chance to increase defense",
            "Chance to evade incoming attack",
            "Switch to another creature",
            "Concede defeat and end the battle",
            "Run from battle",
            "Attempt to catch a wild creature",
            "Forego action",
            "Heal for half max HP",
            "Use an item",
        };

protected:

    Item* _item = nullptr;

    bool _appliedScale = false;
    bool _appliedOffset = false;

public:

    /* enum for which action is to be performed */
    ActionIndex type;

    /* Values to scale HP by */
    float invokerHPScale = 1.0f;
    float targetHPScale = 1.0f;

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

    Creature* invoker = nullptr;
    Creature* target = nullptr;

    CreatureModifier* invokerModifier = nullptr;
    CreatureModifier* targetModifier = nullptr;

public:

    Action(
            ActionIndex actionTypeIndex,
            Creature* invokingCreature,
            Creature* targetedCreature,
            Item* itemToUse = nullptr
        );
    Action(const Action& ref);

    ~Action();

protected:

    /* Enforce that the action is of a valid type */
    void _validate_type();

public:

    /* String literal of action type */
    const char* name() const;

    /* Returns string literal of action description */
    const char* description() const;

protected:

    /* Return dice roll by invoking creature */
    float _get_roll();

private:

    /* Run action

    These should not be called directly;
    instead, use process() and then
    apply_scale() followed by apply_offset() */

    /* Calcualte result if action type is STRIKE */
    void _strike(float multiplier = 1.0f);

    /* Calculate result if action type is MEDITATE */
    void _meditate(float multiplier = 1.0f);

    /* Calculate result if action type is BRACE */
    void _brace(float multiplier = 1.0f);

    /* Calculate result if action type is DODGE */
    void _dodge(float multiplier = 1.0f);

    /* Roll for escape chance */
    void _escape(float multiplier = 1.0f);

    /* Roll for catch chance */
    void _catch(float multiplier = 1.0f);

    /* Do nothing */
    void _pass();

    /* Calculate result if action type is INNERPEACE */
    void _inner_peace();

    // /* Use item on target */
    // void _use_item();

public:

    /* Run the action and calculate result */
    void process(float multiplier = 1.0f);

    /* Apply result to Creatures */
    
    /* Scale values from all simultaneous
    actions first so that subsequent applications
    are not stacked */
    void apply_scale();

    /* Apply offsets */
    void apply_offset();
};

class ActionPair
{

public:

    ActionPair();
    ActionPair(const ActionPair& ref);

    ~ActionPair();

public:

    void process();

};

};

#endif
