#ifndef CREATUREADVENTURES_ACTION_H
#define CREATUREADVENTURES_ACTION_H

#include <memory>

#include "creature.h"

namespace CreatureAdventures
{

class ActionBase;
class Action;
class TieredAction;
class Strike;
class Meditate;
class Brace;
class Dodge;
class InnerPeace;
class Switch;
class Forfeit;
class Escape;
class Catch;
class Pass;

/* Actions are taken by creatures to cause
damage or healing during battles.
Some actions may be used outside of battle */

class Action
{

public:

    static constexpr const char* name = "";
    static constexpr const char* description = "";

    Creature* invoker;
    Creature* target;

    bool pvp;

public:

    /* Absolute HP offset result for invoker.
    Can be a positive or negative float value */
    float invokerHPDelta = 0;

    /* Absolute HP offset result for target.
    Can be a positive or negative float value */
    float targetHPDelta = 0;

    /* Did invoker successfully complete an evasive maneuver */
    bool evasive = false;

    /* Did invoker fail to make contact or did target evade */
    bool evaded = false;

public:

    Action();
    Action(
            Creature* actionInvoker,
            Creature* actionTarget
        );
    Action(const Action& ref);

    ~Action();

    /* Modifies target creature's HP.
    Positive values add HP (heal),
    negative values remove HP (damage) */
    void offset_target_hp(float targetHPOffset);

    /* Modifies action invoking creature's HP.
    Positive values add HP (heal),
    negative values remove HP (damage) */
    void offset_invoker_hp(float invokerHPOffset);
    
    /* Takes positive value as argument
    and applies it as a negative hp offset
    to target (damage) */
    void damage_target(float targetHPLost);

    /* Takes positive value as argument
    and applies it as a negative hp offset
    to invoker (damage) */
    void damage_invoker(float invokerHPLost);

    /* Return hp deltas to be processed */
    std::pair<float, float> get();

};

class TieredAction : public Action, public TieredObjectBase
{

public:

    TieredAction(int uidNum, int tierNum);
    TieredAction(
            int uidNum,
            int tierNum,
            Creature* actionInvoker,
            Creature* actionTarget
        );
    
    ~TieredAction();

};

class Strike : public Action
{

public:

    static constexpr const char* name = "Strike";
    static constexpr const char* description = "Attack an enemy for damage";

public:

    Strike();
    Strike(
            Creature* actionInvoker,
            Creature* actionTarget
        );

    ~Strike();

};

class Meditate : public Action
{

public:

    static constexpr const char* name = "Meditate";
    static constexpr const char* description = "Roll to increase attack";

public:

    Meditate();
    Meditate(
            Creature* actionInvoker,
            Creature* actionTarget
        );

    ~Meditate();

};

class Brace : public Action
{

public:

    static constexpr const char* name = "Brace";
    static constexpr const char* description = "Roll to increase defense";

public:

    Brace();
    Brace(
            Creature* actionInvoker,
            Creature* actionTarget
        );

    ~Brace();

};

class Dodge : public Action
{

public:

    static constexpr const char* name = "Dodge";
    static constexpr const char* description = "Roll to evade incoming attack";

public:

    Dodge();
    Dodge(
            Creature* actionInvoker,
            Creature* actionTarget
        );

    ~Dodge();

};

class InnerPeace : public Action
{

public:

    static constexpr const char* name = "InnerPeace";
    static constexpr const char* description = "Heal for half max HP";

public:

    InnerPeace();
    InnerPeace(
            Creature* actionInvoker,
            Creature* actionTarget
        );

    ~InnerPeace();

};

class Switch : public Action
{

public:

    static constexpr const char* name = "Switch";
    static constexpr const char* description = "Switch to another creature";

public:

    Switch();
    Switch(
            Creature* actionInvoker,
            Creature* actionTarget
        );

    ~Switch();

};

class Forfeit : public Action
{

public:

    static constexpr const char* name = "Forfeit";
    static constexpr const char* description = "Concede defeat and end the battle";

public:

    Forfeit();
    Forfeit(
            Creature* actionInvoker,
            Creature* actionTarget
        );

    ~Forfeit();

};

class Escape : public Action
{

public:

    static constexpr const char* name = "Escape";
    static constexpr const char* description = "Run from battle";

public:

    Escape();
    Escape(
            Creature* actionInvoker,
            Creature* actionTarget
        );

    ~Escape();

};

class Catch : public Action
{

public:

    static constexpr const char* name = "Catch";
    static constexpr const char* description = "Attempt to catch a wild creature";

public:

    Catch();
    Catch(
            Creature* actionInvoker,
            Creature* actionTarget
        );

    ~Catch();

};

class Pass : public Action
{

public:

    static constexpr const char* name = "Pass";
    static constexpr const char* description = "Forego action";

public:

    Pass();
    Pass(
            Creature* actionInvoker,
            Creature* actionTarget
        );
    ~Pass();

};

};

#endif
