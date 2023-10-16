#include "tieredobjectbase.h"

namespace CreatureAdventures
{

// template <typename T>
// auto _check_uid_match(T obj, int uidToCheck)
// {
//     return (obj.uid == uidToCheck);
// }

// template <typename T>
// std::vector<T>::iterator match_uid(std::vector<T> vec, int uidNum)
// {
//     // auto match = [&uidNum](auto obj){return obj.uid == uidNum;};
//     // return std::find_if(
//     //         vec.begin(),
//     //         vec.end(),
//     //         match
//     //     );
//     for (
//             typename std::vector<T>::iterator it;
//             it != vec.end();
//             ++it
//         )
//     {
//         if (it.uid == uidNum)
//         {
//             return it;
//         }
//     }
//     return vec.end();
// }

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

};