#ifndef CREATUREADVENTURESACTION_H
#define CREATUREADVENTURESACTION_H

#include "creature.h"

namespace CreatureAdventures
{

/* Base class for Actions */

class ActionBase
{

public:

    std::string name;
    std::string description;

    Creature invoker;
    Creature target;

    bool pvp;

public:

    ActionBase();
    ~ActionBase();

    virtual void run();
    std::pair<int, int> get();

};

/* Actions are taken by creatures to cause
damage or healing during battles.
Some actions may be used outside of battle */

class Action : public ActionBase
{

public:

    /* HP gained or lost for each creature.
    Can be a positive or negative integer */
    int invokerHPDelta = 0;
    int targetHPDelta = 0;

    /* Did invoker successfully complete an evasive maneuver */
    bool evasive;

    /* Did invoker fail to make contact or did target evade */
    bool evaded;

public:

    Action();
    ~Action();

    /* Modifies target creature's HP.
    Positive values add HP (heal),
    negative values remove HP (damage) */
    void offset_target_hp(int targetHPOffset);

    /* Modifies action invoking creature's HP.
    Positive values add HP (heal),
    negative values remove HP (damage) */
    void offset_invoker_hp(int invokerHPOffset);
    
    /* Takes positive value as argument
    and applies it as a negative hp offset
    to target (damage) */
    void damage_target(int targetHPLost);

    /* Takes positive value as argument
    and applies it as a negative hp offset
    to invoker (damage) */
    void damage_invoker(int invokerHPLost);
    
    /* Return hp deltas to be processed */
    std::pair<int, int> get();

};

class TieredAction : public Action, public TieredObjectBase
{

public:

    TieredAction(Creature invoker, Creature target);

};

class Pass : public Action
{

public:

    std::string name = "Pass";
    std::string description = "Forego action";

public:

    Pass();
    ~Pass();

};

class Catch : public Action
{

public:

    std::string name = "Catch";
    std::string description = "Attempt to catch a wild creature";

public:

    Catch();
    ~Catch();

};

class Strike : public Action
{

public:

    std::string name = "Strike";
    std::string description = "Attack an enemy for damage";

public:

    Strike();
    ~Strike();

    void run() override;

};

class Meditate : public Action
{

public:

    std::string name = "Meditate";
    std::string description = "Roll to increase attack";

public:

    Meditate();
    ~Meditate();

    void run() override;

};

class Brace : public Action
{

public:

    std::string name = "Brace";
    std::string description = "Roll to increase defense";

public:

    Brace();
    ~Brace();

    void run() override;

};

class Dodge : public Action
{

public:

    std::string name = "Dodge";
    std::string description = "Roll to evade incoming attack";

public:

    Dodge();
    ~Dodge();

    void run() override;

};

class InnerPeace : public Action
{

public:

    std::string name = "InnerPeace";
    std::string description = "Heal for half max HP";

public:

    InnerPeace();
    ~InnerPeace();

    void run() override;

};

class Switch : public ActionBase
{

public:

    std::string name = "Switch";
    std::string description = "Switch to another creature";

public:

    Switch();
    ~Switch();

};

class Forfeit : public ActionBase
{

public:

    std::string name = "Forfeit";
    std::string description = "Concede defeat and end the battle";

public:

    Forfeit();
    ~Forfeit();

};

class Escape : public ActionBase
{

public:

    std::string name = "Escape";
    std::string description = "Run from battle";

public:

    Escape();
    ~Escape();

};

};

#endif
