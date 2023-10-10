#ifndef CREATUREADVENTURES_CREATURE_H
#define CREATUREADVENTURES_CREATURE_H

#include "tieredobjectbase.h"

namespace CreatureAdventures
{

class Action;

class ModifierBase : public TieredObjectBase
{

public:

    int numTurns;
    bool timed;
    bool activeDuringCombat;

public:

    ModifierBase(int uidNum, int tierNum);
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

public:

    CreatureModifier(int uidNum, int tierNum);
    CreatureModifier(const CreatureModifier& ref);

    ~CreatureModifier();

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

protected:

    float _currentHP;

public:

    std::vector<CreatureModifier> modifiers;
    std::vector<Action*> availableActions;

public:

    Creature(int uidNum, int tierNum);
    Creature(const Creature& ref);

    ~Creature();

    void set_owner(std::string ownerName);
    std::string get_owner() const;

    void _set_permanent_attack(float value);
    float _get_permanent_attack() const;
    float get_attack() const;
    
    void _set_permanent_defense(float value);
    float _get_permanent_defense() const;
    float get_defense() const;
    
    void set_max_hp(float value);
    float get_max_hp() const;
    
    void set_hp(float value);
    float get_hp() const;
    
    void set_name(std::string nameStr);
    std::string name() const;

    void add_modifier(const CreatureModifier& modifier);
    void remove_modifier(const CreatureModifier& modifier);

    void heal(float value);

};

};

#endif