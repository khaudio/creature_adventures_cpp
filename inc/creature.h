#ifndef CREATUREADVENTURESCREATURE_H
#define CREATUREADVENTURESCREATURE_H

#include "tieredobjectbase.h"

namespace CreatureAdventures
{

extern class Action;

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

    int attackModifier;
    int defenseModifier;
    int hpModifier;

public:

    CreatureModifier();
    ~CreatureModifier();

};

class CreatureBase : public TieredObjectBase
{

public:

    int baseAttack;
    int baseDefense;
    int baseMaxHP;

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

    int attackModifier = 0;
    int defenseModifier = 0;
    int hpModifier = 0;

protected:

    int _currentHP;

public:

    std::vector<ModifierBase> modifiers;
    std::vector<Action> availableActions;

public:

    Creature(std::string playerName);
    ~Creature();

    void _set_permanent_attack(int value);
    int _get_permanent_attack();
    int get_attack();
    
    void _set_permanent_defense(int value);
    int _get_permanent_defense();
    int get_defense();
    
    void set_max_hp(int value);
    int get_max_hp();
    
    void set_hp(int value);
    int get_hp();
    
    void set_name(std::string nameStr);
    std::string name();

    void add_modifier(ModifierBase modifier);
    void remove_modifier(ModifierBase modifier);

    void heal(int additionalHP = 0);

};

};

#endif