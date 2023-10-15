#ifndef CREATUREADVENTURES_ITEM_H
#define CREATUREADVENTURES_ITEM_H

#include "tieredobjectbase.h"
#include <sstream>

#include <cmath>

namespace CreatureAdventures
{

class Item;
class Potion;
class Poison;
class Elixir;
class Revive;
class Bait;

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

    /* Number of available item types */
    static constexpr const int numTypes = 5;

    static constexpr const int staticTypeIndex = -1;

public:

    /* Item type index; i.e., Potion, Poision, Elixir, etc. */
    int typeIndex;

    /* Whether itme is persistent after use */
    bool persistent;

    /* Positive or negative float */
    float value;

    std::vector<const char*> additionalEffects;

public:

    Item(
            int uidNum,
            int tierNum,
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

    static constexpr const int staticTypeIndex = 0;

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

    static constexpr const int staticTypeIndex = 1;

public:

    Poison(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    Poison(const Poison& ref);

    ~Poison();

};

class Elixir: public Item
{

public:

    static constexpr const char* name = "Elixir";
    static constexpr const char* description = "Raises attack or defense power of a creature";

    static constexpr const int staticTypeIndex = 2;

public:

    Elixir(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    Elixir(const Elixir& ref);

    ~Elixir();

};

class Revive: public Item
{

public:

    static constexpr const char* name = "Revive";
    static constexpr const char* description = "Revives a creature with depleted HP";

    static constexpr const int staticTypeIndex = 3;

public:

    Revive(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    Revive(const Revive& ref);

    ~Revive();

};

class Bait: public Item
{

public:

    static constexpr const char* name = "Bait";
    static constexpr const char* description = "Raises chances of successfully catching wild creatures";

    static constexpr const int staticTypeIndex = 4;

public:

    Bait(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    Bait(const Bait& ref);

    ~Bait();

};

};

#endif
