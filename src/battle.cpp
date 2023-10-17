#include "battle.h"

namespace CreatureAdventures
{

Battle::Battle() :
_aggressorActive(true),
_defenderActive(true),
_isDraw(false),
aggressor(nullptr),
defender(nullptr)
{
}

Battle::Battle(Creature* attackingCreature, Creature* defendingCreature) :
_aggressorActive(true),
_defenderActive(true),
_isDraw(false),
aggressor(attackingCreature),
defender(defendingCreature)
{
}

Battle::Battle(const Battle& ref) :
_aggressorActive(ref._aggressorActive),
_defenderActive(ref._defenderActive),
_isDraw(ref._isDraw),
aggressor(ref.aggressor),
defender(ref.defender)
{
}

Battle::~Battle()
{
}

bool Battle::active()
{
    return (
            this->_aggressorActive
            && this->_defenderActive
            && (this->aggressor->get_hp() > 0)
            && (this->defender->get_hp() > 0)
        );
}

Creature* Battle::result()
{
    this->_aggressorActive = (
            (this->aggressor->get_hp() > 0)
            ? this->_aggressorActive
            : false
        );
    this->_defenderActive = (
            (this->defender->get_hp() > 0)
            ? this->_defenderActive
            : false
        );

    if (active())
    {
        return nullptr;
    }

    if (this->_aggressorActive && (!this->_defenderActive))
    {
        return this->aggressor;
    }
    else if ((!this->_aggressorActive) && this->_defenderActive)
    {
        return this->defender;
    }
    else if (!(this->_aggressorActive && this->_defenderActive))
    {
        this->_isDraw = true;
    }

    return nullptr;
}

void Battle::strike(Action action, Creature* invoker, Creature* target)
{
    
    // {0.0, 0.0}
    // {0.2, 0.3}
    // {0.4, 0.97}
    // {0.97, 1.0}
}

void Battle::_switch_creatures(
        Creature* exitingCreature,
        Creature* enteringCreature
    )
{
    #if _DEBUG
    if (
            (exitingCreature == nullptr)
            || (enteringCreature == nullptr)
        )
    {
        throw std::invalid_argument("Creature is null");
    }
    #endif

    switch (exitingCreature->uid)
    {
        case (this->aggressor->uid):
            #if _DEBUG
            if (enteringCreature->uid == this->defender->uid)
            {
                throw std::invalid_argument("Creature may not battle itself");
            }
            #endif
            this->aggressor = enteringCreature;
            return;
        case (this->defender->uid):
            #if _DEBUG
            if (enteringCreature->uid == this->aggressor->uid)
            {
                throw std::invalid_argument("Creature may not battle itself");
            }
            #endif
            this->defender = enteringCreature;
            return;
        default:
            throw std::out_of_range("Exiting creature not found in battle");
    }
}

Action Battle::_get_next_action(std::deque<Action>* queue)
{
    Action action = queue->front();
    queue->pop_front();
    return action;
}

void Battle::process_single_action(
        Action action,
        Creature* invoker,
        Creature* target
    )
{
    DEBUG_OUT("Processing action...\n");

    switch (action.type)
    {
        case (FORFEIT):

            /* Invoker forfeits */
            this->_aggressorActive = (
                    (invoker == this->aggressor)
                    ? false
                    : this->_aggressorActive
                );
            this->_defenderActive = (
                    (invoker == this->defender)
                    ? false
                    : this->_defenderActive
                );
            return;

        case (PASS):

            /* Invoker does nothing */
            return;

        case (SWITCH):

            /* Target is creature to switch to */
            if (target->get_hp() <= 0)
            {
                throw std::invalid_argument("Creature hp must be > 0\n");
            }
            _switch_creatures(invoker, target);
            return;

        case (ESCAPE):

            /* Attempt to end the battle */
            ;
    }

    /* Save the action in case it is repeated */
    this->_lastAggressorAction = (
            (invoker->uid == this->aggressor->uid)
            ? action
            : this->_lastAggressorAction
        );
    this->_lastDefenderAction = (
            (invoker->uid == this->defender->uid)
            ? action
            : this->_lastDefenderAction
        );
}

void Battle::process_action_pair_from_queue()
{
    #if _DEBUG
    if (this->_aggressorActionQueue.empty())
    {
        throw std::out_of_range("Aggressor action queue empty");
    }
    else if (this->_defenderActionQueue.empty())
    {
        throw std::out_of_range("Defender action queue empty");
    }
    if (!active())
    {
        throw std::logic_error("Battle not in active state\n");
    }
    #endif

    Action aggressorAction(_get_next_action(&this->_aggressorActionQueue));
    Action defenderAction(_get_next_action(&this->_defenderActionQueue));

}

};