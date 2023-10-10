#include "tieredobjectbase.h"

namespace CreatureAdventures
{

TieredObjectBase::TieredObjectBase(int uidNum, int tierNum) :
uid(uidNum),
tier(tierNum)
{
}

TieredObjectBase::TieredObjectBase(const TieredObjectBase& ref) :
uid(ref.uid),
tier(ref.tier)
{
}

TieredObjectBase::~TieredObjectBase()
{
}


};