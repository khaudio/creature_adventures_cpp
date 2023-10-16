#include "battle.h"

namespace CreatureAdventures
{

Battle::Battle() :
_aggressorActive(true),
_defenderActive(true),
_isDraw(false)
{
}

Battle::Battle(const Battle& ref) :
_aggressorActive(ref._aggressorActive),
_defenderActive(ref._defenderActive),
_isDraw(ref._isDraw)
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
            && (this->aggressor.hp > 0)
            && (this->defender.hp > 0)
        );
}

Creature* Battle::result()
{
    this->_aggressorActive = (
            (this->aggressor.hp > 0)
            ? this->_aggressorActive
            : false
        );
    this->_defenderActive = (
            (this->defender.hp > 0)
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

void _switch_creatures(
        Creature* aggresingCreature,
        Creature* defendingCreature
    )
{
    #if _DEBUG
    if (aggressingCreature->uid == defendingCreature->uid)
    {
        throw std::invalid_argument("Creatures cannot battle themselves");
    }
    #endif

    this->aggressor = aggressingCreature;
    this->defender = defendingCreature;
}

Action Battle::_get_next_action(std::deque<Action>* queue)
{
    Action action = queue->front();
    queue->pop_front();
    return action;
}

void Battle::process_single_action(Action action, Creature* invoker, Creature* target)
{
    DEBUG_OUT("Processing action...\n");

    switch (action.typeIndex)
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

            /* Do nothing */
            return;

        case (SWITCH):

            /* Target is creature to switch to */
            if (target->hp <= 0)
            {
                throw std::invalid_argument("Creature hp must be > 0\n");
            }
            _switch_creatures(invoker, target);
            return;

        case (ESCAPE):

            /* Attempt to end the battle */
            ;

    }
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