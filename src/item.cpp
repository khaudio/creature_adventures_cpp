#include "item.h"

namespace CreatureAdventures
{

Item::Item(
        int uidNum,
        int tierNum,
        int itemTypeIndex,
        float maxPossibleValue,
        bool isPersistent
    ) :
TieredObjectBase(uidNum, tierNum),
typeIndex(itemTypeIndex),
persistent(isPersistent)
{
    #if _DEBUG
    auto iter = std::find(
            Item::types.begin(),
            Item::types.end(),
            this->typeIndex
        );
    if (iter == Item::types.end())
    {
        throw std::out_of_range("Item type index not found");
    }
    #endif

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
    #if _DEBUG
    auto iter = std::find(
            Item::types.begin(),
            Item::types.end(),
            this->typeIndex
        );
    if (iter == Item::types.end())
    {
        throw std::out_of_range("Item type index not found");
    }
    #endif
}

Item::~Item()
{
}

float Item::get()
{
    return this->value;
}

const char* Item::name() const
{
    return Item::names.at(this->typeIndex);
}

const char* Item::description() const
{
    return Item::descriptions.at(this->typeIndex);
}

std::vector<const char*> Item::additional_effects() const
{
    std::vector<const char*> additionalEffects;
    
    switch (this->typeIndex)
    {
        case POISON:
            additionalEffects.emplace_back("Ignores defense");
            break;
        case ELIXIR:
        case BAIT:
            additionalEffects.emplace_back("Lasts until end of battle");
            break;
    }
    return additionalEffects;
}

};
