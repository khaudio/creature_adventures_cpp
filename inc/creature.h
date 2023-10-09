#ifndef CREATUREADVENTURESCREATURE_H
#define CREATUREADVENTURESCREATURE_H

#include "tieredobjectbase.h"

namespace CreatureAdventures
{

class Action;

class ModifierBase
{

public:

    int uid;
    int numTurns;
    bool timed;
    bool activeDuringCombat;

public:

    ModifierBase();
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

    CreatureModifier();
    ~CreatureModifier();

};

class CreatureBase : public TieredObjectBase
{

public:

    float baseAttack;
    float baseDefense;
    float baseMaxHP;

public:

    CreatureBase();
    ~CreatureBase();

};

class Creature : public CreatureBase
{

public:

    std::string owner;
    std::string baseName;
    std::string nickname;

    float attackModifier = 0;
    float defenseModifier = 0;
    float hpModifier = 0;

protected:

    float _currentHP;

public:

    std::vector<ModifierBase> modifiers;
    std::vector<Action> availableActions;

public:

    Creature();
    ~Creature();

    void set_owner(std::string ownerName);
    std::string get_owner();

    void _set_permanent_attack(float value);
    float _get_permanent_attack();
    float get_attack();
    
    void _set_permanent_defense(float value);
    float _get_permanent_defense();
    float get_defense();
    
    void set_max_hp(float value);
    float get_max_hp();
    
    void set_hp(float value);
    float get_hp();
    
    void set_name(std::string nameStr);
    std::string name();

    void add_modifier(ModifierBase modifier);
    void remove_modifier(ModifierBase modifier);

    void heal(float additionalHP);

};

};

#endif