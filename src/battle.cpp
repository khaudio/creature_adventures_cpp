#include "battle.h"

namespace CreatureAdventures
{

// Battle::Battle() :
// _aggressorActive(true),
// _defenderActive(true),
// _isDraw(false),
// aggressor(nullptr),
// defender(nullptr),
// pvp(false),
// _lastAggressorAction(PASS, this->aggressor, this->defender),
// _lastDefenderAction(PASS, this->defender, this->aggressor)
// {
// }

// Battle::Battle(
//         Creature* attackingCreature,
//         Creature* defendingCreature,
//         bool isPvp
//     ) :
// _aggressorActive(true),
// _defenderActive(true),
// _isDraw(false),
// aggressor(attackingCreature),
// defender(defendingCreature),
// pvp(isPvp),
// _lastAggressorAction(PASS, this->aggressor, this->defender),
// _lastDefenderAction(PASS, this->defender, this->aggressor)
// {
// }

// Battle::Battle(const Battle& ref) :
// _aggressorActive(ref._aggressorActive),
// _defenderActive(ref._defenderActive),
// _isDraw(ref._isDraw),
// aggressor(ref.aggressor),
// defender(ref.defender),
// _lastAggressorAction(ref._lastAggressorAction),
// _lastDefenderAction(ref._lastDefenderAction)
// {
// }

// Battle::~Battle()
// {
// }

// void Battle::_validate_action(Action action)
// {
//     #if _DEBUG
//     if (
//             (action.invoker == nullptr)
//             || (action.target == nullptr)
//         )
//     {
//         throw std::invalid_argument("Creature is null");
//     }
//     else if (action.target->get_hp() <= 0)
//     {
//         throw std::invalid_argument("Creature hp must be > 0");
//     }
//     #endif

// }

// bool Battle::active()
// {
//     return (
//             this->_aggressorActive
//             && this->_defenderActive
//             && (this->aggressor->get_hp() > 0)
//             && (this->defender->get_hp() > 0)
//         );
// }

// Creature* Battle::result()
// {
//     this->_aggressorActive = (
//             (this->aggressor->get_hp() > 0)
//             ? this->_aggressorActive
//             : false
//         );
//     this->_defenderActive = (
//             (this->defender->get_hp() > 0)
//             ? this->_defenderActive
//             : false
//         );

//     if (active())
//     {
//         return nullptr;
//     }

//     if (this->_aggressorActive && (!this->_defenderActive))
//     {
//         return this->aggressor;
//     }
//     else if ((!this->_aggressorActive) && this->_defenderActive)
//     {
//         return this->defender;
//     }
//     else if (!(this->_aggressorActive && this->_defenderActive))
//     {
//         this->_isDraw = true;
//     }

//     return nullptr;
// }

// void Battle::forfeit(Action action)
// {
//     this->_aggressorActive = (
//             (action.invoker == this->aggressor)
//             ? false
//             : this->_aggressorActive
//         );
//     this->_defenderActive = (
//             (action.invoker == this->defender)
//             ? false
//             : this->_defenderActive
//         );
//     return;
// }

// void Battle::switch_creatures(Action action)
// {
//     #if _DEBUG
//     if (
//             (action.invoker == nullptr)
//             || (action.target == nullptr)
//         )
//     {
//         throw std::invalid_argument("Creature is null");
//     }
//     else if (action.target->get_hp() <= 0)
//     {
//         throw std::invalid_argument("Creature hp must be > 0");
//     }
//     #endif

//     switch (action.invoker->uid)
//     {
//         case (this->aggressor->uid):
//             #if _DEBUG
//             if (action.target == this->defender)
//             {
//                 throw std::invalid_argument("Creature may not battle itself");
//             }
//             #endif
//             this->aggressor = action.target;
//             return;
//         case (this->defender->uid):
//             #if _DEBUG
//             if (action.target == this->aggressor)
//             {
//                 throw std::invalid_argument("Creature may not battle itself");
//             }
//             #endif
//             this->defender = action.target;
//             return;
//         default:
//             throw std::out_of_range("Exiting creature not found in battle");
//     }
// }

// // Action Battle::_get_next_action(std::deque<Action>* queue)
// // {
// //     Action action = queue->front();
// //     queue->pop_front();
// //     return action;
// // }

// void Battle::process_single_action(Action action)
// {
//     DEBUG_OUT("Processing action...\n");

//     switch (action.type)
//     {
//         case (FORFEIT):

//             /* Invoker forfeits */
//             forfeit(action);
//             break;

//         case (PASS):

//             /* Invoker does nothing */
//             break;

//         case (SWITCH):

//             /* Target is creature to switch to */
//             switch_creatures(action);
//             break;

//         case (ESCAPE):

//             /* Attempt to end the battle */
//             escape(action);
//             break;
        
//         case (STRIKE):

//             /* Invoker attempts to strike target for damage */
//             strike(action);
//             break;
        
//         case (MEDITATE):
//             action.process();
//             action.apply();
//             break;

//     }

//     /* Save the action in case it is repeated */
//     this->_lastAggressorAction = (
//             (action.invoker == this->aggressor)
//             ? action
//             : this->_lastAggressorAction
//         );
//     this->_lastDefenderAction = (
//             (action.invoker == this->defender)
//             ? action
//             : this->_lastDefenderAction
//         );
// }

// void Battle::process_action_pair_from_queue()
// {
//     #if _DEBUG
//     if (this->_aggressorActionQueue.empty())
//     {
//         throw std::out_of_range("Aggressor action queue empty");
//     }
//     else if (this->_defenderActionQueue.empty())
//     {
//         throw std::out_of_range("Defender action queue empty");
//     }
//     if (!active())
//     {
//         throw std::logic_error("Battle not in active state\n");
//     }
//     #endif

//     Action aggressorAction(_get_next_action(&this->_aggressorActionQueue));
//     Action defenderAction(_get_next_action(&this->_defenderActionQueue));

// }

};