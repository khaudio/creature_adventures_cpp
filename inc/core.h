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

class CoreBase : public TieredObjectBase
{

public:

    /* Default max stat points available for all creature creation */
    float maxPossibleStatPoints = 30.0;

    float maxPossibleCatchChance;

public:

    CoreBase(int uidNum, int tierNum);
    ~CoreBase();

};

};

#endif
