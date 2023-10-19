#include "action.h"

namespace CreatureAdventures
{

Action::Action(
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

Action::Action(const Action& ref) :
type(ref.type),
invokerHPScaler(ref.invokerHPScaler),
targetHPScaler(ref.targetHPScaler),
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

float Action::_get_roll()
{
    float rollValueMin(0.0), rollValueMax(1.0);

    for (const auto& modifier: invoker->modifiers)
    {
        rollValueMin += modifier.rollMinModifier;
        rollValueMax += modifier.rollMaxModifier;
    }

    return random_multiplier_roll<float>(rollValueMin, rollValueMax);
}

void Action::_strike(float multiplier)
{
    #if _DEBUG
    if (this->type != STRIKE)
    {
        throw std::logic_error("Invalid function for action type");
    }
    #endif

    float roll(_get_roll() * multiplier);

    if (roll < 0.12f)
    {
        /* Miss */
        this->evaded = true;

        DEBUG_OUT(this->invoker->uid << " misses " << this->target->uid << '\n');
    }
    else if ((0.12f <= roll) && (roll < 0.2f))
    {
        /* Deflected hit with counterstrike by target */
        this->targetHPOffset -= (
                this->invoker->get_attack()
                - this->target->get_defense()
            );
        this->invokerHPOffset -= (
                this->target->get_attack()
                - this->invoker->get_defense()
            );

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

void Action::_meditate(float multiplier)
{
    #if _DEBUG
    if (this->type != MEDITATE)
    {
        throw std::logic_error("Invalid function for action type");
    }
    #endif

    float roll(_get_roll() * multiplier);
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
        modifier.attackModifier = (std::round(
                this->invoker->_get_persistent_attack()
                * 0.3f
            ));

        DEBUG_OUT(" for +30% persistent attack power");
        DEBUG_OUT(" (" << this->invoker->get_attack() << ")\n");
    }
    else if ((0.6f <= roll) && (roll < 0.92f))
    {
        /* +50% attack */
        modifier.attackModifier = (std::round(
                this->invoker->_get_persistent_attack()
                * 0.5f
            ));

        DEBUG_OUT(" for +50% persistent attack power");
        DEBUG_OUT(" (" << this->invoker->get_attack() << ")\n");
    }
    else if (0.92f <= roll)
    {
        /* +100% attack */
        modifier.attackModifier = (std::round(
                this->invoker->_get_persistent_attack()
                * 1.0f
            ));

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

    if (modifier.attackModifier)
    {
        this->invoker->add_modifier(modifier);
    }
}

void Action::_brace(float multiplier)
{
    #if _DEBUG
    if (this->type != BRACE)
    {
        throw std::logic_error("Invalid function for action type");
    }
    #endif

    float roll(_get_roll() * multiplier);
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
        modifier.defenseModifier = (std::round(
                this->invoker->_get_persistent_defense()
                * 0.5f
            ));

        DEBUG_OUT(" for +50% persistent defense");
        DEBUG_OUT(" (" << this->invoker->get_defense() << ")\n");
    }
    else if ((0.6f <= roll) && (roll < 0.92f))
    {
        /* +100% defense */
        modifier.defenseModifier = (std::round(
                this->invoker->_get_persistent_defense()
                * 1.0f
            ));

        DEBUG_OUT(" for +100% persistent defense");
        DEBUG_OUT(" (" << this->invoker->get_defense() << ")\n");
    }
    else if (0.92f <= roll)
    {
        /* +200% defense */
        modifier.defenseModifier = (std::round(
                this->invoker->_get_persistent_defense()
                * 2.0f
            ));

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

    if (modifier.defenseModifier)
    {
        this->invoker->add_modifier(modifier);
    }

}

void Action::_dodge(float multiplier)
{
    #if _DEBUG
    if (this->type != DODGE)
    {
        throw std::logic_error("Invalid function for action type");
    }
    #endif

    float roll(_get_roll() * multiplier * invoker->evasiveness);

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

void Action::_inner_peace()
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

void Action::_escape(float multiplier)
{
    float roll(_get_roll() * multiplier * invoker->evasiveness);

}

void Action::_catch(float multiplier)
{
    float roll(_get_roll() * multiplier);

}

void Action::process(float multiplier)
{
    switch (this->type)
    {
        case (STRIKE):
            _strike(multiplier);
            break;
        case (MEDITATE):
            _meditate(multiplier);
            break;
        case (BRACE):
            _brace(multiplier);
            break;
        case (DODGE):
            _dodge(multiplier);
            break;
        case (ESCAPE):
            _escape(multiplier);
            break;
        case (CATCH):
            _catch(multiplier);
            break;
        case (INNERPEACE):
            _inner_peace();
            break;
    }
}

void Action::apply()
{
    if (this->applied)
    {
        throw std::logic_error("Invalid; Action already applied");
    }

    if (!this->evaded)
    {
        float invokerHP = this->invoker->get_hp();
        float targetHP = this->target->get_hp();

        invokerHP *= this->invokerHPScaler;
        invokerHP += this->invokerHPOffset;

        targetHP *= this->targetHPScaler;
        targetHP += this->targetHPOffset;

        this->invoker->set_hp(invokerHP);
        this->target->set_hp(targetHP);
    }

    this->applied = true;
}

};
