#include "item.h"

namespace CreatureAdventures
{

Item::Item(
        int uidNum,
        int tierNum,
        int itemType,
        float maxPossibleValue,
        bool isPersistent
    ) :
TieredObjectBase(uidNum, tierNum),
persistent(isPersistent)
{
    if (itemType > itemTypes.size())
    {
        throw std::out_of_range("Invalid item type index");
    }
    this->itemTypeIndex = itemType;
    this->value = std::round(
            this->tierQualityThresholds[this->tier].first
            * static_cast<float>(maxPossibleValue)
        );
}

Item::Item(const Item& ref) :
TieredObjectBase(ref),
itemTypeIndex(ref.itemTypeIndex),
persistent(ref.persistent),
value(ref.value),
additionalEffects(ref.additionalEffects)
{
}

Item::~Item()
{
}

float Item::get()
{
    return this->value;
}

std::vector<const char*> Item::get_additional_effects()
{
    return this->additionalEffects;
}

Potion::Potion(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, 0, maxPossibleValue, isPersistent)
{
}

Potion::Potion(const Potion& ref) :
Item(ref)
{
}

Potion::~Potion()
{
}

Poison::Poison(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, 1, maxPossibleValue, isPersistent)
{
    this->additionalEffects.emplace_back("Ignores defense");
}

Poison::~Poison()
{
}

Elixir::Elixir(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, 2, maxPossibleValue, isPersistent)
{
    this->additionalEffects.emplace_back("Lasts until end of battle");
}

Elixir::~Elixir()
{
}

Revive::Revive(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, 3, maxPossibleValue, isPersistent)
{
}

Revive::~Revive()
{
}

Bait::Bait(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, 4, maxPossibleValue, isPersistent)
{
    this->additionalEffects.emplace_back("Lasts until end of battle");
}

Bait::~Bait()
{
}

};
