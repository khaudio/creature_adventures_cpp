#ifndef CREATUREADVENTURES_TIEREDOBJECTBASE_H
#define CREATUREADVENTURES_TIEREDOBJECTBASE_H

#include <vector>
#include <string>
#include <utility>
#include <map>

namespace CreatureAdventures
{

class TieredObjectBase
{

public:

    /* Names for each tier, indicating quality */
    constexpr static const std::vector<std::string> tierNames = {
            "Common",
            "Uncommon",
            "Rare",
            "Epic",
            "Legendary"
        };

    /* Relative ratios of how many objects of each tier should be created.
    No Legendary objects by default */
    constexpr static const std::vector<float> tierVolumeRatios = {
            0.56,
            0.26,
            0.12,
            0.06,
            0.00
        };

    /* Relative ratios of stat points available to items in each tier */
    constexpr static const std::vector<std::pair<float, float>> tierQualityThresholds = {
            {0.50, 0.56},
            {0.56, 0.63},
            {0.63, 0.70},
            {0.70, 0.80},
            {0.80, 1.00}
        };
    
    constexpr static const int numTiers = 5;

public:

    int uid;
    int tier;

public:

    TieredObjectBase(int uidNum, int tierNum);
    ~TieredObjectBase();

    std::string tier_name(int index) const;

};

};

#endif
