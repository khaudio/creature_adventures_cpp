#ifndef CREATUREADVENTURES_CREATURE_H
#define CREATUREADVENTURES_CREATURE_H

#include "tieredobjectbase.h"
#include "modifier.h"

namespace CreatureAdventures
{

/* Declarations */

class CreatureModifier;
class Creature;

/* Modifiers to creature attributes.
Can optionally expire after
numTurns if timed is set to True.
value can be a positive or negative integer. */

class CreatureModifier : public ModifierBase
{

public:

    float attackScale = 1.0f;
    float defenseScale = 1.0f;
    float hpScale = 1.0f;
    float evasivenessScale = 1.0f;

    float attackOffset = 0;
    float defenseOffset = 0;
    float hpOffset = 0;
    float evasivenessOffset = 0;

    float rollMinOffset = 0;
    float rollMaxOffset = 0;

public:

    CreatureModifier();
    CreatureModifier(const CreatureModifier& ref);

    ~CreatureModifier();

    friend bool operator==(
            const CreatureModifier& left,
            const CreatureModifier& right
        )
    {
        return (left.uid == right.uid);
    }

};

class Creature : public TieredObjectBase
{

protected:

    static inline int uidIndex = 0;

public:

    /* Base values should not be altered */
    float baseAttack;
    float baseDefense;
    float baseMaxHP;

    /* Multiplier for effectiveness of evasion;
    i.e., 1.0 is normal evasiveness */
    float baseEvasiveness;

    std::string owner;
    std::string baseName;
    std::string nickname;

    /* Persistent modifiers; always >= 0 */
    float attackModifier = 0;
    float defenseModifier = 0;
    float hpModifier = 0;
    float evasivenessModifier = 0;

protected:

    float _currentHP;

public:

    /* Temporary modifiers */
    std::vector<CreatureModifier> modifiers;

public:

    Creature(TierIndex tierNum);
    Creature(const Creature& ref);

    ~Creature();

    void set_owner(std::string ownerName);
    std::string get_owner() const;

    /* Base attack plus object modifier value */
    void _set_persistent_attack(float value);
    float _get_persistent_attack() const;

    /* Persistent attack plus all modifiers */
    float get_attack() const;

    /* Base defense plus object modifier value */
    void _set_persistent_defense(float value);
    float _get_persistent_defense() const;

    /* Persistent defense plus all modifiers */
    float get_defense() const;

    /* Persistent maximum hp plus all modifiers */
    void _set_persistent_max_hp(float value);
    float _get_persistent_max_hp() const;

    /* Maximum possible HP */
    float get_max_hp() const;

    /* Current HP */
    void set_hp(float value);
    float get_hp() const;

    /* Base evasiveness plus object modifier value */
    void _set_persistent_evasiveness(float value);
    float _get_persistent_evasiveness() const;

    /* Persistent evasiveness plus all modifiers */
    float get_evasiveness() const;

    /* Creature name */
    void set_name(std::string nameStr);
    std::string name() const;

    void add_modifier(const CreatureModifier& modifier);
    void remove_modifier(const CreatureModifier& modifier);

    void decrement_modifiers();

    void heal(float value);

};

};

#endif