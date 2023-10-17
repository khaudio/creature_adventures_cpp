#include "tieredobjectbase.h"

namespace CreatureAdventures
{

template <typename T>
void trim_minimum(T* value, T minimum)
{
    *value = (*value >= minimum ? *value : minimum);
}

template <typename T>
void trim_maximum(T* value, T maximum)
{
    *value = (*value <= maximum ? *value : maximum);
}


TieredObjectBase::TieredObjectBase(int uidNum, TierIndex tierNum) :
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

template void trim_minimum<float>(float*, float);
template void trim_minimum<double>(double*, double);

template void trim_maximum<float>(float*, float);
template void trim_maximum<double>(double*, double);

};
