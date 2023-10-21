#include "modifier.h"

namespace CreatureAdventures
{

ModifierBase::ModifierBase() :
uid(ModifierBase::uidIndex++),
numTurns(0)
{
}

ModifierBase::ModifierBase(const ModifierBase& ref) :
uid(ref.uid),
numTurns(ref.numTurns),
persistent(ref.persistent)
{
}

ModifierBase::~ModifierBase()
{
}

};