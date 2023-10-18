#include "player.h"

namespace CreatureAdventures
{

PlayerBase::PlayerBase(int playerUidNum) :
_human(false),
_activeCreature(nullptr),
uid(playerUidNum)
{
    std::copy(
            Action::types.begin(),
            Action::types.end(),
            this->_availableActions.begin()
        );
    this->creatures.reserve(3);
}

PlayerBase::PlayerBase(const PlayerBase& ref) :
_human(ref._human),
_activeCreature(ref._activeCreature),
_availableActions(ref._availableActions),
_artifacts(ref._artifacts),
uid(ref.uid),
level(ref.level),
assignableAttributePoints(ref.assignableAttributePoints),
name(ref.name),
creatures(ref.creatures),
items(ref.items)
{
}

PlayerBase::~PlayerBase()
{
}

Creature* PlayerBase::get_active_creature() const
{
    return this->_activeCreature;
}

void PlayerBase::set_active_creature(Creature* creature)
{
    for (Creature* c: this->creatures)
    {
        if (c == creature)
        {
            this->_activeCreature = c;
            return;
        }
    }
    throw std::out_of_range("Creature not found");
}

void PlayerBase::set_active_creature(int uidNum)
{
    for (Creature* c: this->creatures)
    {
        if (c->uid == uidNum)
        {
            this->_activeCreature = c;
            return;
        }
    }
    throw std::out_of_range("Creature not found");
}

bool PlayerBase::has_artifact(ArtifactIndex index) const
{
    auto iter = std::find(
            this->_artifacts.begin(),
            this->_artifacts.end(),
            index
        );
    return !(iter == this->_artifacts.end());
}

void PlayerBase::level_up()
{
    this->assignableAttributePoints += this->level;
}

Player::Player(int uidNum, std::string playerName) :
PlayerBase(uidNum)
{
    this->_human = true;
    this->name = playerName;
}

Player::Player(const Player& ref) :
PlayerBase(ref),
_catchChance(ref._catchChance)
{
}

Warlord::Warlord(int uidNum) :
PlayerBase(uidNum)
{
    this->_human = false;
}

Warlord::Warlord(const Warlord& ref) :
PlayerBase(ref)
{
}

Warlord::~Warlord()
{
}

Gladiator::Gladiator(int uidNum) :
PlayerBase(uidNum)
{
    this->_human = false;
}

Gladiator::Gladiator(const Gladiator& ref) :
PlayerBase(ref)
{
}

Gladiator::~Gladiator()
{
}

};
