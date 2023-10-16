#include "action.h"

namespace CreatureAdventures
{

Action::Action(ActionIndex actionTypeIndex) :
type(actionTypeIndex)
{
    #if _DEBUG
    auto iter = std::find(
            Action::types.begin(),
            Action::types.end(),
            this->type
        );
    if (iter == types.end())
    {
        throw std::out_of_range("Action type index not found");
    }
    #endif
}

Action::Action(const Action& ref) :
type(ref.type),
pvp(ref.pvp),
invokerHPDelta(ref.invokerHPDelta),
targetHPDelta(ref.targetHPDelta),
evasive(ref.evasive),
evaded(ref.evaded)
{
    #if _DEBUG
    auto iter = std::find(
            Action::types.begin(),
            Action::types.end(),
            this->type
        );
    if (iter == types.end())
    {
        throw std::out_of_range("Action type index not found");
    }
    #endif
}

Action::~Action()
{
}

const char* Action::name() const
{
    return Action::names.at(this->type);
}

const char* Action::description() const
{
    return Action::descriptions.at(this->type);
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

void Action::process(Creature* invoker, Creature* target)
{
    // float multiplier = random_multiplier_roll<float>();
}

};