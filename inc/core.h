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

    CoreBase(int uidNum, int tierNum);
    ~CoreBase();

};

};

#endif
