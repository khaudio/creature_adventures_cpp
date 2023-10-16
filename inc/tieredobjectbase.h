#ifndef CREATUREADVENTURES_TIEREDOBJECTBASE_H
#define CREATUREADVENTURES_TIEREDOBJECTBASE_H

#include "defs.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace CreatureAdventures
{

class TieredObjectBase;

class Creature;
class Item;

enum TierIndex
{
    COMMON = 0,
    UNCOMMON = 1,
    RARE = 2,
    EPIC = 3,
    LEGENDARY = 4,
};

// template <typename T>
// std::vector<T>::iterator match_uid(std::vector<T> vec, int uidNum);

class TieredObjectBase
{

public:

    static constexpr const int numTiers = 5;

    /* Names for each tier, indicating quality */
    static constexpr const std::array<const char*, TieredObjectBase::numTiers> tierNames = {
            "Common",
            "Uncommon",
            "Rare",
            "Epic",
            "Legendary"
        };

    /* Relative ratios of how many objects of each tier should be created.
    No Legendary objects by default */
    static constexpr const std::array<float, TieredObjectBase::numTiers> tierVolumeRatios = {
            0.56f,
            0.26f,
            0.12f,
            0.06f,
            0.00f
        };

    /* Relative ratios of stat points available to items in each tier */
    static constexpr const std::array<std::pair<float, float>, TieredObjectBase::numTiers> tierQualityThresholds = {{
            {0.50f, 0.56f},
            {0.56f, 0.63f},
            {0.63f, 0.70f},
            {0.70f, 0.80f},
            {0.80f, 1.00f}
        }};

public:

    int uid;
    TierIndex tier;

public:

    TieredObjectBase(int uidNum, TierIndex tierNum);
    TieredObjectBase(const TieredObjectBase& ref);

    ~TieredObjectBase();

};

};

#endif
