#ifndef CREATUREADVENTURES_ITEM_H
#define CREATUREADVENTURES_ITEM_H

#include "tieredobjectbase.h"
#include <sstream>

#include <cmath>

namespace CreatureAdventures
{

class Item : public TieredObjectBase
{

public:

    /* Relative ratios of stat points available to items in each tier */
    static constexpr const std::array<std::pair<float, float>, 5> tierQualityThresholds = {{
            {0.22f, 0.22f},
            {0.34f, 0.34f},
            {0.67f, 0.67f},
            {0.80f, 0.80f},
            {1.00f, 1.00f}
        }};

    /* Names of each item type */
    static constexpr const std::array<const char*, 5> itemTypes = {
            "Potion",
            "Poison",
            "Elixir",
            "Revive",
            "Bait"
        };

    /* Item name */
    static constexpr const char* name = "";

    /* Item description */
    static constexpr const char* description = "";

public:

    /* Item type index; i.e., Potion, Poision, Elixir, etc. */
    int itemTypeIndex;

    /* Whether itme is persistent after use */
    bool persistent;

    /* Positive or negative float */
    float value;

    std::vector<const char*> additionalEffects;

public:

    Item(
            int uidNum,
            int tierNum,
            int itemType,
            float maxPossibleValue,
            bool isPersistent = false
        );
    Item(const Item& ref);

    ~Item();

    virtual float get();
    virtual std::vector<const char*> get_additional_effects();

};

class Potion: public Item
{

public:

    static constexpr const char* name = "Potion";
    static constexpr const char* description = "Heals a creature for a specified amount";

public:

    Potion(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    Potion(const Potion& ref);

    ~Potion();

};

class Poison: public Item
{

public:

    static constexpr const char* name = "Poison";
    static constexpr const char* description = "Poisons an enemy creature for unmitigated damage";

public:

    Poison(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    ~Poison();

};

class Elixir: public Item
{

public:

    static constexpr const char* name = "Elixir";
    static constexpr const char* description = "Raises attack or defense power of a creature";

public:

    Elixir(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    ~Elixir();

};

class Revive: public Item
{

public:

    static constexpr const char* name = "Revive";
    static constexpr const char* description = "Revives a creature with depleted HP";

public:

    Revive(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    ~Revive();

};

class Bait: public Item
{

public:

    static constexpr const char* name = "Bait";
    static constexpr const char* description = "Raises chances of successfully catching wild creatures";

public:

    Bait(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    ~Bait();

};

};

#endif
