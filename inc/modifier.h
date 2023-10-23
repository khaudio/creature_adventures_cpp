#ifndef CREATUREADVENTURES_MODIFIER_H
#define CREATUREADVENTURES_MODIFIER_H

namespace CreatureAdventures
{

/* Declarations */
class ModifierBase;

class ModifierBase
{

protected:

    static inline int uidIndex = 0;

public:

    int uid;

    /* Whether modifier persists through
    revival after HP is depleted */
    bool persistent = false;

    /* Lifetime of the modifier
    in number of actions performed 
    if persistent is false.

    Set to (n + 1), as it
    should immediately decrement on
    the same turn it is applied. */
    int numTurns = 0;

public:

    ModifierBase();
    ModifierBase(const ModifierBase& ref);

    ~ModifierBase();

};

};

#endif
