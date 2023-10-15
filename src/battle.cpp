#include "battle.h"

namespace CreatureAdventures
{

Battle::Battle()
{
}

Battle::Battle(const Battle& ref)
{
}

Battle::~Battle()
{
}

bool Battle::active()
{
    return (
            (this->aggressor.hp > 0)
            && (this->defender.hp > 0)
        );
}

void Battle::_update_action_queue_creature(
        Creature* oldCreature,
        Creature* newCreature,
        std::deque<Action> queue
    )
{
    for (auto action: queue)
    {
        if (action.invoker->uid == oldCreature->uid)
        {
            action.invoker = newCreature;
        }
        if (action.target->uid == oldCreature->uid)
        {
            action.target = newCreature;
        }
    }
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

    if (aggressingCreature->uid != this->aggressor->uid)
    {
        _update_action_queue_creature(
                this->aggresor,
                aggressingCreature,
                &this->_aggressorActionQueue
            );
    }
    if (defendingCreature->uid != this->defender->uid)
    {
        _update_action_queue_creature(
                this->defender,
                defendingCreature,
                &this->_defenderActionQueue
            );
    }
    this->aggressor = aggressingCreature;
    this->defender = defendingCreature;
}

Action Battle::_get_next_action(std::deque<Action>* queue)
{
    Action action = queue->front();
    queue->pop_front();
    return action;
}

void Battle::process_single_action(Action action)
{
    DEBUG_OUT("Processing action...\n");

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
    #endif

    Action aggressorAction(_get_next_action(&this->_aggressorActionQueue));
    Action defenderAction(_get_next_action(&this->_defenderActionQueue));

    

}

};