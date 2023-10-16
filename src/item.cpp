#include "item.h"

namespace CreatureAdventures
{

Item::Item(
        int uidNum,
        TierIndex tierNum,
        ItemIndex itemTypeIndex,
        float maxPossibleValue,
        bool isPersistent
    ) :
TieredObjectBase(uidNum, tierNum),
type(itemTypeIndex),
persistent(isPersistent)
{
    #if _DEBUG
    _validate_type();
    #endif

    this->value = std::round(
            this->tierQualityThresholds[this->tier].first
            * static_cast<float>(maxPossibleValue)
        );
}

Item::Item(const Item& ref) :
TieredObjectBase(ref),
type(ref.type),
persistent(ref.persistent),
value(ref.value),
additionalEffects(ref.additionalEffects)
{
    #if _DEBUG
    _validate_type();
    #endif
}

void Item::_validate_type()
{
    auto iter = std::find(
            Item::types.begin(),
            Item::types.end(),
            this->type
        );
    if (iter == Item::types.end())
    {
        throw std::out_of_range("Item type index not found");
    }
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
    return Item::names.at(this->type);
}

const char* Item::description() const
{
    return Item::descriptions.at(this->type);
}

std::vector<const char*> Item::additional_effects() const
{
    std::vector<const char*> additionalEffects;
    
    switch (this->type)
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
