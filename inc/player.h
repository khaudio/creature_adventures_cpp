#ifndef CREATUREADVENTURES_PLAYER_H
#define CREATUREADVENTURES_PLAYER_H

#include "creature.h"
#include "item.h"
#include "artifact.h"

namespace CreatureAdventures
{

class PlayerModifier : public ModifierBase
{

public:

    float catchChanceModifier = 0;

};

/* Players control creatures */

class Player
{

protected:

    /* Whether the player is human */
    bool _human;

    /* 0.0 - 1.0 scale for successful catch */
    float _catchChance = 0.5f;

    /* Only one of player's creatures is
    active at a time */
    Creature* _activeCreature = nullptr;

    /* Actions available to the player */
    std::vector<ActionIndex> _availableActions;/* = {
            STRIKE,
            MEDITATE,
            BRACE,
            DODGE,
            SWITCH,
            FORFEIT,
            ESCAPE,
            CATCH,
            PASS,
        };*/

    std::vector<PlayerModifier> _modifiers;

    /* Artifacts possesed by the player */
    std::vector<ArtifactIndex> _artifacts;

public:

    int uid;
    int level = 0;
    int assignableAttributePoints = 0;

    /* Player name */
    std::string name;

    /* Creatures possessed by player */
    std::vector<Creature> creatures;

    /* Items possessed by player */
    std::vector<Item> items;

public:

    Player(int playerUidNum, bool isHuman);
    Player(const Player& ref);

    ~Player();

    bool is_human() const;

    bool has_artifact(ArtifactIndex index) const;

    void set_active_creature(Creature* creature);
    void set_active_creature(int uidNum);
    Creature* get_active_creature() const;

    void set_catch_chance(float value);
    float get_catch_chance() const;

    void level_up();

};

};

#endif
