#include "creature.h"

namespace CreatureAdventures
{

CreatureModifier::CreatureModifier() :
ModifierBase()
{
}

CreatureModifier::CreatureModifier(const CreatureModifier& ref) :
ModifierBase(ref),
attackScale(ref.attackScale),
defenseScale(ref.defenseScale),
hpScale(ref.hpScale),
evasivenessScale(ref.evasivenessScale),
attackOffset(ref.attackOffset),
defenseOffset(ref.defenseOffset),
hpOffset(ref.hpOffset),
evasivenessOffset(ref.evasivenessOffset),
rollMinOffset(ref.rollMinOffset),
rollMaxOffset(ref.rollMaxOffset)
{
}

CreatureModifier::~CreatureModifier()
{
}

Creature::Creature(TierIndex tierNum) :
TieredObjectBase(Creature::uidIndex++, tierNum),
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
baseEvasiveness(ref.baseEvasiveness),
owner(ref.owner),
baseName(ref.baseName),
nickname(ref.nickname),
attackModifier(ref.attackModifier),
defenseModifier(ref.defenseModifier),
hpModifier(ref.hpModifier),
evasivenessModifier(ref.evasivenessModifier),
_currentHP(ref._currentHP),
modifiers(std::vector<CreatureModifier>(ref.modifiers))
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
    #if _DEBUG
    if (value < 0)
    {
        throw std::invalid_argument("Attack must be >= 0");
    }
    #endif

    this->attackModifier = value - this->baseAttack;

    /* Minimum attack 0 */
    trim_minimum<float>(&this->attackModifier, 0);
}

float Creature::_get_persistent_attack() const
{
    return (this->baseAttack + this->attackModifier);
}

float Creature::get_attack() const
{
    float scale(1.0);
    float offset(0.0);
    float value(_get_persistent_attack());

    for (const auto& mod: this->modifiers)
    {
        scale += (1.0f - mod.attackScale);
        offset += mod.attackOffset;
    }

    value *= scale;
    value += offset;

    /* Minimum attack 0 */
    trim_minimum<float>(&value, 0);

    return std::round(value);
}

void Creature::_set_persistent_defense(float value)
{
    #if _DEBUG
    if (value < 0)
    {
        throw std::invalid_argument("Defense must be >= 0");
    }
    #endif

    this->defenseModifier = value - this->baseDefense;

    /* Minimum defense 0 */
    trim_minimum<float>(&this->defenseModifier, 0);
}

float Creature::_get_persistent_defense() const
{
    return (this->baseDefense + this->defenseModifier);
}

float Creature::get_defense() const
{
    float scale(1.0);
    float offset(0.0);
    float value(_get_persistent_defense());

    for (const auto& mod: this->modifiers)
    {
        scale += (1.0f - mod.defenseScale);
        offset += mod.defenseOffset;
    }

    value *= scale;
    value += offset;

    /* Minimum defense 0 */
    trim_minimum<float>(&value, 0);

    return std::round(value);
}

void Creature::_set_persistent_max_hp(float value)
{
    #if _DEBUG
    if (value <= 0)
    {
        throw std::invalid_argument("Max HP must be > 0");
    }
    #endif

    this->hpModifier = value - this->baseMaxHP;

    /* Minimum HP 1 */
    trim_minimum<float>(&this->hpModifier, 1);
}

float Creature::_get_persistent_max_hp() const
{
    return (this->baseMaxHP + this->hpModifier);
}

float Creature::get_max_hp() const
{
    float scale(1.0);
    float offset(0.0);
    float value(_get_persistent_max_hp());

    for (const auto& mod: this->modifiers)
    {
        scale += (1.0f - mod.hpScale);
        offset += mod.hpOffset;
    }

    value *= scale;
    value += offset;

    /* Minimum HP 1 */
    trim_minimum<float>(&value, 1);

    return std::round(value);
}

void Creature::set_hp(float value)
{
    float trimmed(value);
    trim_minimum<float>(&trimmed, 0);
    trim_maximum<float>(&trimmed, get_max_hp());
    this->_currentHP = std::round(trimmed);
}

float Creature::get_hp() const
{
    return this->_currentHP;
}

void Creature::_set_persistent_evasiveness(float value)
{
    #if _DEBUG
    if (value < 0)
    {
        throw std::invalid_argument("Evasiveness must be >= 0");
    }
    #endif

    this->evasivenessModifier = value - this->baseEvasiveness;

    /* Minimum evasiveness 0 */
    trim_minimum<float>(&this->evasivenessModifier, 0);
}

float Creature::_get_persistent_evasiveness() const
{
    return (this->baseEvasiveness + this->evasivenessModifier);
}

float Creature::get_evasiveness() const
{
    float value(_get_persistent_evasiveness());
    float scale(1.0);
    float offset(0.0);

    for (const auto& modifier: this->modifiers)
    {
        scale += (1.0f - modifier.evasivenessScale);
        offset += modifier.evasivenessOffset;
    }

    value *= scale;
    value += offset;

    trim_minimum<float>(&value, 0);

    return value;
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

void Creature::decrement_modifiers()
{
    bool shrink(false);
    for (CreatureModifier modifier: this->modifiers)
    {
        --modifier.numTurns;
        if (
                (modifier.numTurns == 0)
                || ((!modifier.persistent) && (!get_hp()))
            )
        {
            remove_modifier(modifier);
            shrink = true;

            DEBUG_OUT("Removing expired modifier from " << this->uid << '\n');

        }
        #if _DEBUG
        else if (modifier.numTurns < 0)
        {
            throw std::out_of_range("numTurns should be >= 0");
        }
        #endif
    }

    if (shrink)
    {
        this->modifiers.shrink_to_fit();
    }
}

};