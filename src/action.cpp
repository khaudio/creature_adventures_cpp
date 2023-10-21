#include "action.h"

namespace CreatureAdventures
{

CombatAction::CombatAction(
        ActionIndex actionTypeIndex,
        Creature* invokingCreature,
        Creature* targetedCreature
    ) :
type(actionTypeIndex),
invoker(invokingCreature),
target(targetedCreature)
{
    #if _DEBUG
    _validate_type();
    #endif
}

CombatAction::CombatAction(const CombatAction& ref) :
type(ref.type),
invokerHPScale(ref.invokerHPScale),
targetHPScale(ref.targetHPScale),
invokerHPOffset(ref.invokerHPOffset),
targetHPOffset(ref.targetHPOffset),
evasive(ref.evasive),
evaded(ref.evaded),
invoker(ref.invoker),
target(ref.target)
{
    #if _DEBUG
    _validate_type();
    #endif
}

CombatAction::~CombatAction()
{
}

void CombatAction::_validate_type()
{
    auto iter = std::find(
            CombatAction::types.begin(),
            CombatAction::types.end(),
            this->type
        );
    if (iter == types.end())
    {
        throw std::out_of_range("Action type index not found");
    }
}

const char* CombatAction::name() const
{
    return CombatAction::names.at(this->type);
}

const char* CombatAction::description() const
{
    return CombatAction::descriptions.at(this->type);
}

void CombatAction::_strike(float roll)
{
    #if _DEBUG
    if (this->type != STRIKE)
    {
        throw std::logic_error("Invalid function for action type");
    }
    #endif

    if (roll < this->target->get_evasiveness())
    {
        /* Target evades */
        this->evaded = true;

        DEBUG_OUT(this->target->uid << " evaded " << this->invoker->uid << '\n');
    }
    else if (roll < 0.07f)
    {
        /* Miss */
        this->evaded = true;

        DEBUG_OUT(this->invoker->uid << " misses " << this->target->uid << '\n');
    }
    else if ((0.07f <= roll) && (roll < 0.17f))
    {
        /* Deflected hit with counterstrike by target */
        float damageToTarget = (
                this->invoker->get_attack()
                - this->target->get_defense()
            );
        float damageToInvoker = (
                this->target->get_attack()
                - this->invoker->get_defense()
            );

        trim_minimum<float>(&damageToTarget, 0);
        trim_minimum<float>(&damageToInvoker, 0);

        this->targetHPOffset -= damageToTarget;
        this->invokerHPOffset -= damageToInvoker;

        DEBUG_OUT(this->invoker->uid << " hits " << this->target->uid);
        DEBUG_OUT(" (deflected) for " << this->targetHPOffset << " HP; ");
        DEBUG_OUT(this->target->uid << " counterstrikes (deflected) for ");
        DEBUG_OUT(this->invokerHPOffset << " HP\n");
    }
    else if ((0.17f <= roll) && (roll < 0.89f))
    {
        /* Deflected hit */
        this->targetHPOffset -= (
                this->invoker->get_attack()
                - this->target->get_defense()
            );

        DEBUG_OUT(this->invoker->uid << " hits " << this->target->uid);
        DEBUG_OUT(" (deflected) for " << this->targetHPOffset << " HP\n");
    }
    else if ((0.89f <= roll) && (roll < 0.97f))
    {
        /* Unmitigated hit */
        this->targetHPOffset -= this->invoker->get_attack();

        DEBUG_OUT(this->invoker->uid << " hits " << this->target->uid);
        DEBUG_OUT(" (unmitigated) for " << this->targetHPOffset << " HP\n");
    }
    else if (0.97f <= roll)
    {
        /* Critical hit */
        this->targetHPOffset -= (
                (this->invoker->get_attack() * 2.0f)
                - this->target->get_defense()
            );

        DEBUG_OUT(this->invoker->uid << " hits " << this->target->uid);
        DEBUG_OUT(" (critical) for " << this->targetHPOffset << " HP\n");
    }
    #if _DEBUG
    else
    {
        /* Path should never be reached */
        throw std::out_of_range("Invalid roll value");
    }
    #endif
}

void CombatAction::_meditate(float roll)
{
    #if _DEBUG
    if (this->type != MEDITATE)
    {
        throw std::logic_error("Invalid function for action type");
    }
    #endif

    CreatureModifier modifier;
    modifier.numTurns = 2;

    DEBUG_OUT(this->invoker->uid << " meditates");
    if ((0 <= roll) && (roll < 0.1f))
    {
        /* No change */
        DEBUG_OUT(" for no change to persistent attack power\n");
    }
    else if ((0.1f <= roll) && (roll < 0.6f))
    {
        /* +30% attack */
        modifier.attackScale = 1.3f;

        DEBUG_OUT(" for +30% persistent attack power");
        DEBUG_OUT(" (" << this->invoker->get_attack() << ")\n");
    }
    else if ((0.6f <= roll) && (roll < 0.92f))
    {
        /* +50% attack */
        modifier.attackScale = 1.5f;

        DEBUG_OUT(" for +50% persistent attack power");
        DEBUG_OUT(" (" << this->invoker->get_attack() << ")\n");
    }
    else if (0.92f <= roll)
    {
        /* +100% attack */
        modifier.attackScale = 2.0f;

        DEBUG_OUT(" for +100% persistent attack power");
        DEBUG_OUT(" (" << this->invoker->get_attack() << ")\n");
    } 
    #if _DEBUG
    else
    {
        /* Path should never be reached */
        throw std::out_of_range("Invalid roll value");
    }
    #endif

    if (modifier.attackScale != 1.0f)
    {
        this->invoker->add_modifier(modifier);
    }
}

void CombatAction::_brace(float roll)
{
    #if _DEBUG
    if (this->type != BRACE)
    {
        throw std::logic_error("Invalid function for action type");
    }
    #endif

    CreatureModifier modifier;
    modifier.numTurns = 2;

    DEBUG_OUT(this->invoker->uid << " braces");
    if ((0 <= roll) && (roll < 0.1f))
    {
        /* No change */
        DEBUG_OUT(" for no change to persistent defense\n");
    }
    else if ((0.1f <= roll) && (roll < 0.6f))
    {
        /* +50% defense */
        modifier.defenseScale = 1.5f;

        DEBUG_OUT(" for +50% persistent defense");
        DEBUG_OUT(" (" << this->invoker->get_defense() << ")\n");
    }
    else if ((0.6f <= roll) && (roll < 0.92f))
    {
        /* +100% defense */
        modifier.defenseScale = 2.0f;

        DEBUG_OUT(" for +100% persistent defense");
        DEBUG_OUT(" (" << this->invoker->get_defense() << ")\n");
    }
    else if (0.92f <= roll)
    {
        /* +200% defense */
        modifier.defenseScale = 3.0f;

        DEBUG_OUT(" for +200% persistent defense");
        DEBUG_OUT(" (" << this->invoker->get_defense() << ")\n");
    }
    #if _DEBUG
    else
    {
        /* Path should never be reached */
        throw std::out_of_range("Invalid roll value");
    }
    #endif

    if (modifier.defenseScale != 1.0f)
    {
        this->invoker->add_modifier(modifier);
    }

}

void CombatAction::_dodge(float roll)
{
    #if _DEBUG
    if (this->type != DODGE)
    {
        throw std::logic_error("Invalid function for action type");
    }
    #endif

    roll *= invoker->get_evasiveness();

    DEBUG_OUT(this->invoker->uid << " dodges");
    if ((0 <= roll) && (roll < 0.6f))
    {
        /* Unsuccessful dodge */
        this->evasive = false;

        DEBUG_OUT(" unsuccessfully\n");
    }
    else if (0.6f <= roll)
    {
        /* Successful dodge */
        this->evasive = true;

        DEBUG_OUT(" successfully\n");
    }
    #if _DEBUG
    else
    {
        /* Path should never be reached */
        throw std::out_of_range("Invalid roll value");
    }
    #endif
}

void CombatAction::_pass()
{
    #if _DEBUG
    DEBUG_OUT(this->invoker->uid << " passes\n");
    #endif
}

void CombatAction::_inner_peace()
{
    #if _DEBUG
    if (this->type != INNERPEACE)
    {
        throw std::logic_error("Invalid function for action type");
    }
    #endif

    this->invokerHPOffset += (this->invoker->get_max_hp() * 0.5f);

    DEBUG_OUT(this->invoker->uid << " casts Inner Peace and heals itself");
    DEBUG_OUT(" for " << (this->invoker->get_max_hp() * 0.5f) << '\n');
}

void CombatAction::process(float roll)
{
    switch (this->type)
    {
        case (STRIKE):
            _strike(roll);
            break;
        case (MEDITATE):
            _meditate(roll);
            break;
        case (BRACE):
            _brace(roll);
            break;
        case (DODGE):
            _dodge(roll);
            break;
        case (PASS):
            _pass();
            break;
        case (INNERPEACE):
            _inner_peace();
            break;
    }
}

void CombatAction::apply_scale()
{
    if (this->_appliedScale)
    {
        throw std::logic_error("Invalid; Action scale already applied");
    }

    if (!this->evaded)
    {
        this->invoker->set_hp(this->invoker->get_hp() * this->invokerHPScale);
        this->target->set_hp(this->target->get_hp() * this->targetHPScale);
    }

    this->_appliedScale = true;
}

void CombatAction::apply_offset()
{
    if (this->_appliedOffset)
    {
        throw std::logic_error("Invalid; Action scale already applied");
    }

    if (!this->evaded)
    {
        this->invoker->set_hp(this->invoker->get_hp() + this->invokerHPOffset);
        this->target->set_hp(this->target->get_hp() + this->targetHPOffset);
    }

    this->_appliedOffset = true;
}

};
