#include "tieredobjectbase.h"

namespace CreatureAdventures
{

TieredObjectBase::TieredObjectBase(int uidNum, int tierNum) :
uid(uidNum),
tier(tierNum)
{
}

TieredObjectBase::~TieredObjectBase()
{
}

std::string TieredObjectBase::tier_name(int index) const
{
    return this->tierNames[index];
}

};