#include "creature.h"

namespace CreatureAdventures
{

ModifierBase::ModifierBase(int uidNum, int tierNum) :
TieredObjectBase(uidNum, tierNum),
numTurns(0),
timed(false),
activeDuringCombat(false)
{
}

ModifierBase::ModifierBase(const ModifierBase& ref) :
TieredObjectBase(ref),
numTurns(ref.numTurns),
timed(ref.timed),
activeDuringCombat(ref.activeDuringCombat)
{
}

ModifierBase::~ModifierBase()
{
}

CreatureModifier::CreatureModifier(int uidNum, int tierNum) :
ModifierBase(uidNum, tierNum),
attackModifier(0),
defenseModifier(0),
hpModifier(0)
{
}

CreatureModifier::CreatureModifier(const CreatureModifier& ref) :
ModifierBase(ref),
attackModifier(ref.attackModifier),
defenseModifier(ref.defenseModifier),
hpModifier(ref.hpModifier)
{
}

CreatureModifier::~CreatureModifier()
{
}

Creature::Creature(int uidNum, int tierNum) :
TieredObjectBase(uidNum, tierNum),
owner(""),
baseName(""),
nickname("")
{
}

Creature::~Creature()
{
}

Creature::Creature(const Creature& ref) :
TieredObjectBase(ref),
baseAttack(ref.baseAttack),
baseDefense(ref.baseDefense),
baseMaxHP(ref.baseMaxHP),
owner(ref.owner),
baseName(ref.baseName),
nickname(ref.nickname),
attackModifier(ref.attackModifier),
defenseModifier(ref.defenseModifier),
hpModifier(ref.hpModifier),
_currentHP(ref._currentHP),
modifiers(std::vector<CreatureModifier>(ref.modifiers)),
availableActions(std::vector<Action*>(ref.availableActions))
{
}

void Creature::set_owner(std::string ownerName)
{
    this->owner = ownerName;
}

std::string Creature::get_owner() const
{
    return this->owner;
}

void Creature::_set_permanent_attack(float value)
{
    this->attackModifier = value - this->baseAttack;
}

float Creature::_get_permanent_attack() const
{
    return this->baseAttack + this->attackModifier;
}

float Creature::get_attack() const
{
    float sum(0.0);
    for (const auto& mod: this->modifiers)
    {
        sum += mod.attackModifier;
    }
    return (this->baseAttack + this->attackModifier + sum);
}

void Creature::_set_permanent_defense(float value)
{
    this->defenseModifier = value - this->baseDefense;
}

float Creature::_get_permanent_defense() const
{
    return this->baseDefense + this->defenseModifier;
}

float Creature::get_defense() const
{
    float sum(0.0);
    for (const auto& mod: this->modifiers)
    {
        sum += mod.defenseModifier;
    }
    return (this->baseDefense + this->defenseModifier + sum);
}

void Creature::set_max_hp(float value)
{
    this->hpModifier = value - this->baseMaxHP;
}

float Creature::get_max_hp() const
{
    float sum(0.0);
    for (const auto& mod: this->modifiers)
    {
        sum += mod.hpModifier;
    }
    return (this->baseMaxHP + this->hpModifier + sum);
}

void Creature::set_hp(float value)
{
    float maxHP(get_max_hp());
    if (value >= maxHP)
    {
        this->_currentHP = maxHP;
    }
    else if (value <= 0.0f)
    {
        this->_currentHP = 0;
    }
    else
    {
        this->_currentHP = value;
    }
}

float Creature::get_hp() const
{
    return this->_currentHP;
}

void Creature::set_name(std::string nameStr)
{
    this->nickname = nameStr;
}

std::string Creature::name() const
{
    return ((this->nickname != "") ? this->nickname : this->baseName);
}

void Creature::add_modifier(const CreatureModifier& modifier)
{
    this->modifiers.push_back(modifier);
}

void Creature::remove_modifier(const CreatureModifier& modifier)
{
    std::vector<CreatureModifier>::iterator removable;
    for (auto it = this->modifiers.begin(); it != this->modifiers.end(); ++it)
    {
        if (it->uid == modifier.uid)
        {
            removable = it;
            break;
        }
    }
    this->modifiers.erase(removable);
}

void Creature::heal(float value)
{
    set_hp(value);
}

};