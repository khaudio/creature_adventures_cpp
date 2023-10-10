#include "action.h"

namespace CreatureAdventures
{

ActionBase::ActionBase()
{
}

ActionBase::ActionBase(const ActionBase& ref) :
name(ref.name),
description(ref.description),
invoker(ref.invoker),
target(ref.target),
pvp(ref.pvp)
{
}

ActionBase::~ActionBase()
{
}


Action::Action()
{
}

Action::Action(const Action& ref) :
ActionBase(ref),
invokerHPDelta(ref.invokerHPDelta),
targetHPDelta(ref.targetHPDelta),
evasive(ref.evasive),
evaded(ref.evaded)
{
}

Action::~Action()
{
}

void Action::offset_target_hp(float targetHPOffset)
{
    this->targetHPDelta += targetHPOffset;
}

void Action::offset_invoker_hp(float invokerHPOffset)
{
    this->invokerHPDelta += invokerHPOffset;
}

void Action::damage_target(float targetHPLost)
{
    this->targetHPDelta -= targetHPLost;
}

void Action::damage_invoker(float invokerHPLost)
{
    this->invokerHPDelta -= invokerHPLost;
}

std::pair<float, float> Action::get()
{
    return std::pair<float, float>(
            this->invokerHPDelta,
            this->targetHPDelta
        );
}

};