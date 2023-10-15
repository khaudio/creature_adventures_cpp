#include "action.h"

namespace CreatureAdventures
{

Action::Action()
{
}

Action::Action(
        Creature* actionInvoker,
        Creature* actionTarget
    ) :
invoker(actionInvoker),
target(actionTarget)
{
}

Action::Action(const Action& ref) :
invoker(ref.invoker),
target(ref.target),
pvp(ref.pvp),
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

TieredAction::TieredAction(int uidNum, int tierNum) :
TieredObjectBase(uidNum, tierNum)
{
}

TieredAction::TieredAction(
    int uidNum,
    int tierNum,
    Creature* actionInvoker,
    Creature* actionTarget
    ) :
Action(actionInvoker, actionTarget),
TieredObjectBase(uidNum, tierNum)
{
}

Strike::Strike() :
Action()
{
}

Strike::Strike(
        Creature* actionInvoker,
        Creature* actionTarget
    ) :
Action(actionInvoker, actionTarget)
{
}

Strike::~Strike()
{
}

Meditate::Meditate() :
Action()
{
}

Meditate::Meditate(
        Creature* actionInvoker,
        Creature* actionTarget
    ) :
Action(actionInvoker, actionTarget)
{
}

Meditate::~Meditate()
{
}

Brace::Brace() :
Action()
{
}

Brace::Brace(
        Creature* actionInvoker,
        Creature* actionTarget
    ) :
Action(actionInvoker, actionTarget)
{
}

Brace::~Brace()
{
}

Dodge::Dodge() :
Action()
{
}

Dodge::Dodge(
        Creature* actionInvoker,
        Creature* actionTarget
    ) :
Action(actionInvoker, actionTarget)
{
}

Dodge::~Dodge()
{
}

InnerPeace::InnerPeace() :
Action()
{
}

InnerPeace::InnerPeace(
        Creature* actionInvoker,
        Creature* actionTarget
    ) :
Action(actionInvoker, actionTarget)
{
}

InnerPeace::~InnerPeace()
{
}

Switch::Switch() :
Action()
{
}

Switch::Switch(
        Creature* actionInvoker,
        Creature* actionTarget
    ) :
Action(actionInvoker, actionTarget)
{
}

Switch::~Switch()
{
}

Forfeit::Forfeit() :
Action()
{
}

Forfeit::Forfeit(
        Creature* actionInvoker,
        Creature* actionTarget
    ) :
Action(actionInvoker, actionTarget)
{
}

Forfeit::~Forfeit()
{
}

Escape::Escape() :
Action()
{
}

Escape::Escape(
        Creature* actionInvoker,
        Creature* actionTarget
    ) :
Action(actionInvoker, actionTarget)
{
}

Escape::~Escape()
{
}

Catch::Catch() :
Action()
{
}

Catch::Catch(
        Creature* actionInvoker,
        Creature* actionTarget
    ) :
Action(actionInvoker, actionTarget)
{
}

Catch::~Catch()
{
}

Pass::Pass() :
Action()
{
}

Pass::Pass(
        Creature* actionInvoker,
        Creature* actionTarget
    ) :
Action(actionInvoker, actionTarget)
{
}

Pass::~Pass()
{
}

};
