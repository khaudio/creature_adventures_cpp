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

    bool persistent = false;

    /* Lifetime of the  */
    int numTurns = 1;

public:

    ModifierBase();
    ModifierBase(const ModifierBase& ref);

    ~ModifierBase();

};

};

#endif