#ifndef CREATUREADVENTURES_CREATURE_H
#define CREATUREADVENTURES_CREATURE_H

#include "tieredobjectbase.h"

namespace CreatureAdventures
{

/* Declarations */
class ModifierBase;
class CreatureModifier;
class Creature;

class ModifierBase
{
protected:

    static inline int uidIndex = 0;

public:

    int uid;
    int numTurns;
    bool timed;
    bool activeDuringCombat;

public:

    ModifierBase();
    ModifierBase(const ModifierBase& ref);

    ~ModifierBase();

};

/* Modifiers to creature attributes.
Can optionally expire after
numTurns if timed is set to True.
value can be a positive or negative integer. */

class CreatureModifier : public ModifierBase
{

public:

    float attackModifier;
    float defenseModifier;
    float hpModifier;

    float rollMinModifier = 0;
    float rollMaxModifier = 0;
    float evasivenessModifier = 0;

public:

    CreatureModifier();
    CreatureModifier(const CreatureModifier& ref);

    ~CreatureModifier();

    friend bool operator==(const CreatureModifier& left, const CreatureModifier& right)
    {
        return (left.uid == right.uid);
    }

};

class Creature : public TieredObjectBase
{

public:

    float baseAttack;
    float baseDefense;
    float baseMaxHP;

    std::string owner;
    std::string baseName;
    std::string nickname;

    float attackModifier = 0;
    float defenseModifier = 0;
    float hpModifier = 0;

    /* Multiplier for effectiveness of evasion;
    i.e., 1.0 is normal evasiveness */
    float evasiveness = 1.0f;

protected:

    float _currentHP;

public:

    std::vector<CreatureModifier> modifiers;
    std::vector<ActionIndex> availableActionIndeces = {
            STRIKE,
            MEDITATE,
            BRACE,
            DODGE,
            SWITCH,
            FORFEIT,
            ESCAPE,
            CATCH,
            PASS,
        };

public:

    Creature(int uidNum, TierIndex tierNum);
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

    /* Maximum possible HP */
    void set_max_hp(float value);
    float get_max_hp() const;

    /* Current HP */
    void set_hp(float value);
    float get_hp() const;

    /* Creature name */
    void set_name(std::string nameStr);
    std::string name() const;

    void add_modifier(const CreatureModifier& modifier);
    void remove_modifier(const CreatureModifier& modifier);

    void heal(float value);

};

};

#endif