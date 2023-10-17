#ifndef CREATUREADVENTURES_CORE_H
#define CREATUREADVENTURES_CORE_H

#include "tieredobjectbase.h"
#include "item.h"
#include "creature.h"
#include "action.h"
#include "dice.h"
#include "deck.h"

namespace CreatureAdventures
{
/* Declarations */
class CoreBase;

class CoreBase : public TieredObjectBase
{

public:

    /* Max stat points available for all creature creation */
    static constexpr const float maxPossibleStatPoints = 30.0f;

    /* Max possible value for catching wild creatures */
    static constexpr const float maxPossibleCatchChance = 1.0f;

    

public:

    CoreBase(int uidNum, TierIndex tierNum);
    ~CoreBase();

};

};

#endif
