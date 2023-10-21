#ifndef CREATUREADVENTURES_ITEM_H
#define CREATUREADVENTURES_ITEM_H

#include "tieredobjectbase.h"

namespace CreatureAdventures
{

/* Declarations */
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

protected:

    static inline int uidIndex = 0;

public:

    static constexpr const int numTypes = 5;

    static constexpr const std::array<ItemIndex, Item::numTypes> types = {
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
            "Raises attack power of a creature until it reaches 0 HP",
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
    ItemIndex type;

    /* Whether itme is persistent after use */
    bool persistent;

    /* Positive or negative float */
    float value;

    std::vector<const char*> additionalEffects;

public:

    Item(
            TierIndex tierNum,
            ItemIndex itemTypeIndex,
            float maxPossibleValue,
            bool isPersistent = false
        );
    Item(const Item& ref);

    ~Item();

protected:

    /* Enforce that type is valid */
    void _validate_type();

public:

    float get();

    const char* name() const;
    const char* description() const;
    std::vector<const char*> additional_effects() const;

};

};

#endif
