#ifndef CREATUREADVENTURES_TIEREDOBJECTBASE_H
#define CREATUREADVENTURES_TIEREDOBJECTBASE_H

#include "defs.h"

#include <array>
#include <vector>
#include <string>
#include <string_view>
#include <utility>
#include <map>

namespace CreatureAdventures
{

class TieredObjectBase;

class TieredObjectBase
{

public:

    /* Names for each tier, indicating quality */
    static constexpr const std::array<const char*, 5> tierNames = {
            "Common",
            "Uncommon",
            "Rare",
            "Epic",
            "Legendary"
        };

    /* Relative ratios of how many objects of each tier should be created.
    No Legendary objects by default */
    static constexpr const std::array<float, 5> tierVolumeRatios = {
            0.56f,
            0.26f,
            0.12f,
            0.06f,
            0.00f
        };

    /* Relative ratios of stat points available to items in each tier */
    static constexpr const std::array<std::pair<float, float>, 5> tierQualityThresholds = {{
            {0.50f, 0.56f},
            {0.56f, 0.63f},
            {0.63f, 0.70f},
            {0.70f, 0.80f},
            {0.80f, 1.00f}
        }};

    constexpr static const int numTiers = 5;

public:

    int uid;
    int tier;

public:

    TieredObjectBase(int uidNum, int tierNum);
    TieredObjectBase(const TieredObjectBase& ref);
    
    ~TieredObjectBase();

};

};

#endif
