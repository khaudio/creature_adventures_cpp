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
    inline static const std::vector<std::pair<float, float>> tierQualityThresholds = {
            {0.22f, 0.22f},
            {0.34f, 0.34f},
            {0.67f, 0.67f},
            {0.80f, 0.80f},
            {1.00f, 1.00f}
        };

public:

    /* Item name */
    std::string name;

    /* Item description */
    std::string description;

    std::vector<std::string> additionalEffects;


    /* Whether itme is persistent after use */
    bool persistent;

    /* Positive or negative float */
    float value;

public:

    Item(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    ~Item();

    virtual float get();
    virtual std::vector<std::string> get_description_list();

};

class Potion: public Item
{

public:

    std::string name = "Potion";
    std::string description = "Heals a creature for a specified amount";

public:

    Potion(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    ~Potion();

};

class Poison: public Item
{

public:

    std::string name = "Poison";
    std::string description = "Poisons an enemy creature for unmitigated damage";

public:

    Poison(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    ~Poison();

};

class Elixir: public Item
{

public:

    std::string name = "Elixir";
    std::string description = "Raises attack or defense power of a creature";

public:

    Elixir(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    ~Elixir();

};

class Revive: public Item
{

public:

    std::string name = "Revive";
    std::string description = "Revives a creature with depleted HP";

public:

    Revive(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    ~Revive();

};

class Bait: public Item
{

public:

    std::string name = "Bait";
    std::string description = "Raises chances of successfully catching wild creatures";

public:

    Bait(int uidNum, int tierNum, float maxPossibleValue, bool isPersistent = false);
    ~Bait();

};

};

#endif
