#ifndef CREATUREADVENTURES_PLAYER_H
#define CREATUREADVENTURES_PLAYER_H

#include "creature.h"
#include "item.h"
#include "artifact.h"
#include "action.h"

namespace CreatureAdventures
{

class PlayerBase
{

protected:

    /* Whether the player is human */
    bool _human;

    /* Only one of player's creatures is
    active at a time */
    Creature* _activeCreature;

    /* Actions available to the player */
    std::vector<ActionIndex> _availableActions;

    std::vector<ArtifactIndex> _artifacts;

public:

    int uid;
    int level = 0;
    int assignableAttributePoints = 0;

    /* Player name */
    std::string name;

    /* Creatures possessed by player */
    std::vector<Creature*> creatures;

    /* Creatures possessed by player */
    std::vector<Item*> items;

public:

    PlayerBase(int playerUidNum);
    PlayerBase(const PlayerBase& ref);

    ~PlayerBase();

    Creature* get_active_creature() const;

    void set_active_creature(Creature* creature);
    void set_active_creature(int uidNum);

    bool has_artifact(ArtifactIndex index) const;

    void level_up();

};

class Player : public PlayerBase
{

protected:

    float _catchChance = 1.0f;

public:

    Player(int uidNum, std::string name);
    Player(const Player& ref);

    ~Player();

};

class Warlord : public PlayerBase
{

public:

    Warlord(int uidNum);
    Warlord(const Warlord& ref);

    ~Warlord();

};

class Gladiator : public PlayerBase
{

public:

    Gladiator(int uidNum);
    Gladiator(const Gladiator& ref);

    ~Gladiator();

};

};

#endif
