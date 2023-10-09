#include "item.h"

namespace CreatureAdventures
{

Item::Item(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
TieredObjectBase(uidNum, tierNum),
persistent(isPersistent)
{
    this->tier = tierNum;
    this->value = std::round(
            this->tierQualityThresholds[this->tier].first
            * static_cast<float>(maxPossibleValue)
        );
}

Item::~Item()
{
}

float Item::get()
{
    return this->value;
}

std::vector<std::string> Item::get_description_list()
{
    return this->additionalEffects;
}

Potion::Potion(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
}

Potion::~Potion()
{
}

Poison::Poison(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
    this->additionalEffects.emplace_back("Ignores defense");
}

Poison::~Poison()
{
}

Elixir::Elixir(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
    this->additionalEffects.emplace_back("Lasts until end of battle");
}

Elixir::~Elixir()
{
}

Revive::Revive(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
}

Revive::~Revive()
{
}

Bait::Bait(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
    this->additionalEffects.emplace_back("Lasts until end of battle");
}

Bait::~Bait()
{
}

};
