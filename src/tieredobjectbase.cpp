#include "tieredobjectbase.h"

namespace CreatureAdventures
{

TieredObjectBase::TieredObjectBase()
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