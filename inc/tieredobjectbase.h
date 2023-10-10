#ifndef CREATUREADVENTURES_TIEREDOBJECTBASE_H
#define CREATUREADVENTURES_TIEREDOBJECTBASE_H

#include <vector>
#include <string>
#include <utility>
#include <map>

#if _DEBUG
#include <iostream>
#endif

#ifndef DEBUG_OUT
#if _DEBUG
#define DEBUG_OUT(x) std::cout << x << '\n';
#else
#define DEUBG_OUT(x)
#endif
#endif

#ifndef DEBUG_ERR
#if _DEBUG
#define DEBUG_ERR(x) std::cerr << x << '\n';
#else
#define DEUBG_ERR(x)
#endif
#endif

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
            0.56f,
            0.26f,
            0.12f,
            0.06f,
            0.00f
        };

    /* Relative ratios of stat points available to items in each tier */
    constexpr static const std::vector<std::pair<float, float>> tierQualityThresholds = {
            {0.50f, 0.56f},
            {0.56f, 0.63f},
            {0.63f, 0.70f},
            {0.70f, 0.80f},
            {0.80f, 1.00f}
        };
    
    constexpr static const int numTiers = 5;

public:

    int uid;
    int tier;

public:

    TieredObjectBase(int uidNum, int tierNum);
    TieredObjectBase(const TieredObjectBase& ref);
    
    ~TieredObjectBase();

    constexpr static std::string tier_name(int index)
    {
        return tierNames[index];
    }


};

};

#endif
