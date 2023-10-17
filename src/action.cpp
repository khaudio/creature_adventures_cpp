#include "action.h"

namespace CreatureAdventures
{

Action::Action(ActionIndex actionTypeIndex, bool isPvp) :
type(actionTypeIndex),
pvp(isPvp)
{
    #if _DEBUG
    _validate_type();
    #endif
}

Action::Action(const Action& ref) :
type(ref.type),
pvp(ref.pvp),
invokerHPScaler(ref.invokerHPScaler),
targetHPScaler(ref.targetHPScaler),
invokerHPOffset(ref.invokerHPOffset),
targetHPOffset(ref.targetHPOffset),
evasive(ref.evasive),
evaded(ref.evaded)
{
    #if _DEBUG
    _validate_type();
    #endif
}

Action::~Action()
{
}

void Action::_validate_type()
{
    auto iter = std::find(
            Action::types.begin(),
            Action::types.end(),
            this->type
        );
    if (iter == types.end())
    {
        throw std::out_of_range("Action type index not found");
    }
}

const char* Action::name() const
{
    return Action::names.at(this->type);
}

const char* Action::description() const
{
    return Action::descriptions.at(this->type);
}

void Action::scale_invoker_hp(float value)
{
    this->invokerHPScaler = value;
}

void Action::scale_target_hp(float value)
{
    this->targetHPScaler = value;
}

void Action::offset_invoker_hp(float invokerHPOffset)
{
    this->invokerHPOffset += invokerHPOffset;
}

void Action::offset_target_hp(float targetHPOffset)
{
    this->targetHPOffset += targetHPOffset;
}

float Action::get_invoker_scale()
{
    return this->invokerHPScaler;
}

float Action::get_invoker_offset()
{
    return this->invokerHPOffset;
}

float Action::get_target_scale()
{
    return this->targetHPScaler;
}

float Action::get_target_offset()
{
    return this->targetHPOffset;
}

};
