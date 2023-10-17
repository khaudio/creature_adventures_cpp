#include "creature.h"

namespace CreatureAdventures
{

ModifierBase::ModifierBase() :
uid(ModifierBase::uidIndex++),
numTurns(0),
timed(false),
activeDuringCombat(false)
{
}

ModifierBase::ModifierBase(const ModifierBase& ref) :
uid(ref.uid),
numTurns(ref.numTurns),
timed(ref.timed),
activeDuringCombat(ref.activeDuringCombat)
{
}

ModifierBase::~ModifierBase()
{
}

CreatureModifier::CreatureModifier() :
ModifierBase(),
attackModifier(0),
defenseModifier(0),
hpModifier(0),
rollMinModifier(0),
rollMaxModifier(0)
{
}

CreatureModifier::CreatureModifier(const CreatureModifier& ref) :
ModifierBase(ref),
attackModifier(ref.attackModifier),
defenseModifier(ref.defenseModifier),
hpModifier(ref.hpModifier),
rollMinModifier(ref.rollMinModifier),
rollMaxModifier(ref.rollMaxModifier)
{
}

CreatureModifier::~CreatureModifier()
{
}

Creature::Creature(int uidNum, TierIndex tierNum) :
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
availableActionIndeces(std::vector<ActionIndex>(ref.availableActionIndeces))
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

void Creature::_set_persistent_attack(float value)
{
    this->attackModifier = value - this->baseAttack;

    /* Minimum attack 0 */
    trim_minimum<float>(&this->attackModifier, 0);
}

float Creature::_get_persistent_attack() const
{
    float sum(this->baseAttack + this->attackModifier);

    /* Minimum attack 0 */
    trim_minimum<float>(&sum, 0);

    return sum;
}

float Creature::get_attack() const
{
    float sum(0.0);

    for (const auto& mod: this->modifiers)
    {
        sum += mod.attackModifier;
    }
    sum += (this->baseAttack + this->attackModifier);

    /* Minimum attack 0 */
    trim_minimum<float>(&sum, 0);

    return sum;
}

void Creature::_set_persistent_defense(float value)
{
    this->defenseModifier = value - this->baseDefense;

    /* Minimum HP 1 */
    trim_minimum(&this->defenseModifier, (-(this->baseDefense - 1)));
}

float Creature::_get_persistent_defense() const
{
    float sum(this->baseDefense + this->defenseModifier);

    /* Minimum HP 1 */
    trim_minimum<float>(&sum, (-(this->baseDefense - 1)));

    return sum;
}

float Creature::get_defense() const
{
    float sum(0.0);

    for (const auto& mod: this->modifiers)
    {
        sum += mod.defenseModifier;
    }
    sum += (this->baseDefense + this->defenseModifier);

    /* Minimum HP 1 */
    trim_minimum<float>(&sum, 1);

    return sum;
}

void Creature::set_max_hp(float value)
{
    this->hpModifier = value - this->baseMaxHP;

    /* Minimum HP 1 */
    trim_minimum<float>(&this->hpModifier, 1);
}

float Creature::get_max_hp() const
{
    float sum(0.0);

    for (const auto& mod: this->modifiers)
    {
        sum += mod.hpModifier;
    }
    sum += (this->baseMaxHP + this->hpModifier);

    /* Minimum HP 1 */
    trim_minimum<float>(&sum, 1);

    return sum;
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
        this->_currentHP = std::round(value);
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
    for (auto it = this->modifiers.begin(); it != this->modifiers.end(); ++it)
    {
        if (it->uid == modifier.uid)
        {
            this->modifiers.erase(it);
            return;
        }
    }
}

void Creature::heal(float value)
{
    set_hp(value);
}

};