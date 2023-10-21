#include "player.h"

namespace CreatureAdventures
{

Player::Player(int playerUidNum, bool isHuman) :
_human(isHuman),
uid(playerUidNum)
{
    std::copy(
            Action::types.begin(),
            Action::types.end(),
            this->_availableActions.begin()
        );
    this->creatures.reserve(3);
}

Player::Player(const Player& ref) :
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

Player::~Player()
{
}

bool Player::is_human() const
{
    return this->_human;
}

bool Player::has_artifact(ArtifactIndex index) const
{
    auto iter = std::find(
            this->_artifacts.begin(),
            this->_artifacts.end(),
            index
        );
    return !(iter == this->_artifacts.end());
}

void Player::set_active_creature(Creature* creature)
{
    for (Creature& c: this->creatures)
    {
        if (c == *creature)
        {
            this->_activeCreature = &c;
            return;
        }
    }
    throw std::out_of_range("Creature not found");
}

void Player::set_active_creature(int uidNum)
{
    for (Creature& c: this->creatures)
    {
        if (c.uid == uidNum)
        {
            this->_activeCreature = &c;
            return;
        }
    }
    throw std::out_of_range("Creature not found");
}

Creature* Player::get_active_creature() const
{
    return this->_activeCreature;
}

void Player::level_up()
{
    this->assignableAttributePoints += this->level;
}

};
