#ifndef CREATUREADVENTURES_CORE_H
#define CREATUREADVENTURES_CORE_H

#include "tieredobjectbase.h"

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
