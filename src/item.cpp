#include "item.h"

namespace CreatureAdventures
{

Item::Item(
        int uidNum,
        int tierNum,
        float maxPossibleValue,
        bool isPersistent
    ) :
TieredObjectBase(uidNum, tierNum),
persistent(isPersistent)
{
    this->value = std::round(
            this->tierQualityThresholds[this->tier].first
            * static_cast<float>(maxPossibleValue)
        );
}

Item::Item(const Item& ref) :
TieredObjectBase(ref),
typeIndex(ref.typeIndex),
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
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
    this->typeIndex = Potion::staticTypeIndex;
}

Potion::Potion(const Potion& ref) :
Item(ref)
{
    this->typeIndex = ref.typeIndex;
}

Potion::~Potion()
{
}

Poison::Poison(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
    this->typeIndex = Poison::staticTypeIndex;
    this->additionalEffects.emplace_back("Ignores defense");
}

Poison::Poison(const Poison& ref) :
Item(ref)
{
    this->typeIndex = ref.typeIndex;
}

Poison::~Poison()
{
}

Elixir::Elixir(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
    this->typeIndex = 2;
    this->additionalEffects.emplace_back("Lasts until end of battle");
}

Elixir::Elixir(const Elixir& ref) :
Item(ref)
{
    this->typeIndex = ref.typeIndex;
}

Elixir::~Elixir()
{
}

Revive::Revive(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
    this->typeIndex = 3;
}

Revive::Revive(const Revive& ref) :
Item(ref)
{
    this->typeIndex = ref.typeIndex;
}

Revive::~Revive()
{
}

Bait::Bait(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
    this->typeIndex = 4;
    this->additionalEffects.emplace_back("Lasts until end of battle");
}

Bait::Bait(const Bait& ref) :
Item(ref)
{
    this->typeIndex = ref.typeIndex;
}


Bait::~Bait()
{
}

};
