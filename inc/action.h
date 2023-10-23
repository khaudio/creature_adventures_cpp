#ifndef CREATUREADVENTURES_ACTION_H
#define CREATUREADVENTURES_ACTION_H

#include "dice.h"
#include "creature.h"
#include "item.h"

#include <memory>
#include <set>

namespace CreatureAdventures
{

/* Declarations */
class CombatAction;
class NonCombatAction;
class ActionPair;

void decrement_creature_modifiers();
template <typename T, typename... Types>
void decrement_creature_modifiers(T* c, Types... creatures);

class NonCombatAction
{

public:

    static constexpr const int numTypes = 6;

    static constexpr const std::array<ActionIndex, NonCombatAction::numTypes> types = {
            SWITCH,
            FORFEIT,
            ESCAPE,
            CATCH,
            INNERPEACE,
            USEITEM,
        };

    static constexpr const std::array<const char*, NonCombatAction::numTypes> names = {
            "Switch",
            "Forfeit",
            "Escape",
            "Catch",
            "Inner Peace",
            "Use Item",
        };

    static constexpr const std::array<const char*, NonCombatAction::numTypes> descriptions = {
            "Switch to another creature",
            "Concede defeat and end the battle",
            "Run from battle",
            "Attempt to catch a wild creature",
            "Heal for half max HP",
            "Use an item",
        };

};

class CombatAction
{

public:

    static constexpr const int numTypes = 6;

    static constexpr const std::array<ActionIndex, CombatAction::numTypes> types = {
            STRIKE,
            MEDITATE,
            BRACE,
            DODGE,
            PASS,
            INNERPEACE,
        };

    static constexpr const std::array<const char*, CombatAction::numTypes> names = {
            "Strike",
            "Meditate",
            "Brace",
            "Dodge",
            "Pass",
            "Inner Peace",
        };

    static constexpr const std::array<const char*, CombatAction::numTypes> descriptions = {
            "Attack an enemy for damage",
            "Chance to increase attack",
            "Chance to increase defense",
            "Chance to evade incoming attack",
            "Forego action",
            "Heal for half max HP",
        };

protected:

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

    CombatAction();
    CombatAction(
            ActionIndex actionTypeIndex,
            Creature* invokingCreature,
            Creature* targetedCreature
        );
    CombatAction(const CombatAction& ref);

    ~CombatAction();

protected:

    /* Enforce that the action is of a valid type */
    void _validate_type();

public:

    /* String literal of action type */
    const char* name() const;

    /* Returns string literal of action description */
    const char* description() const;

private:

    /* Run action

    These should not be called directly;
    instead, use process() and then
    apply_scale() followed by apply_offset() */

    /* Calcualte result if action type is STRIKE */
    void _strike(float roll);

    /* Calculate result if action type is MEDITATE */
    void _meditate(float roll);

    /* Calculate result if action type is BRACE */
    void _brace(float roll);

    /* Calculate result if action type is DODGE */
    void _dodge(float roll);

    /* Do nothing */
    void _pass();

    /* Calculate result if action type is INNERPEACE */
    void _inner_peace();

public:

    /* Run the action and calculate result */
    void process(float roll);

    /* Apply result to Creatures */
    
    /* Scale values from all simultaneous
    actions first so that subsequent applications
    are not stacked */
    void apply_scale();

    /* Apply offsets */
    void apply_offset();
};

class CombatActionPair : public std::pair<CombatAction*, CombatAction*>
{

public:

    CombatActionPair();
    CombatActionPair(CombatAction* firstAction, CombatAction* secondAction);
    CombatActionPair(const CombatActionPair& ref);

    ~CombatActionPair();

    void execute();

};

};

#endif
