#ifndef CREATUREADVENTURES_ITEM_H
#define CREATUREADVENTURES_ITEM_H

#include "tieredobjectbase.h"

namespace CreatureAdventures
{

class Item;

enum ItemIndex
{
    POTION = 0,
    POISON = 1,
    ELIXIR = 2,
    REVIVE = 3,
    BAIT = 4
};

class Item : public TieredObjectBase
{

public:

    static constexpr const int numTypes = 5;

    static constexpr const std::array<int, Item::numTypes> types = {
        POTION,
        POISON,
        ELIXIR,
        REVIVE,
        BAIT,
    };

    static constexpr const std::array<const char*, Item::numTypes> names = {
        "Potion",
        "Poison",
        "Elixir",
        "Revive",
        "Bait",
    };

    static constexpr const std::array<const char*, Item::numTypes> descriptions = {
        "Heals a creature for a specified amount",
        "Poisons an enemy creature for unmitigated damage",
        "Raises attack or defense power of a creature",
        "Revives a creature with depleted HP",
        "Raises chances of successfully catching wild creatures",
    };

    /* Relative ratios of stat points available to items in each tier */
    static constexpr const std::array<std::pair<float, float>, Item::numTypes> tierQualityThresholds = {{
            {0.22f, 0.22f},
            {0.34f, 0.34f},
            {0.67f, 0.67f},
            {0.80f, 0.80f},
            {1.00f, 1.00f}
        }};

public:

    /* enum of type of item;
    i.e., Potion, Poision, Elixir, etc. */
    const int typeIndex;

    /* Whether itme is persistent after use */
    bool persistent;

    /* Positive or negative float */
    float value;

    std::vector<const char*> additionalEffects;

public:

    Item(
            int uidNum,
            int tierNum,
            int itemTypeIndex,
            float maxPossibleValue,
            bool isPersistent = false
        );
    Item(const Item& ref);

    ~Item();

    float get();

    const char* name() const;
    const char* description() const;
    std::vector<const char*> additional_effects() const;

};

};

#endif
