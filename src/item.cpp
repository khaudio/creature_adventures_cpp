#include "item.h"

namespace CreatureAdventures
{

Item::Item(int uidNum, int tierNum, int maxPossibleValue, bool isPersistent) :
TieredObjectBase(uidNum, tierNum),
persistent(isPersistent)
{
    this->tier = tierNum;
    this->value = std::round(
            this->tierQualityThresholds[this->tier].first
            * static_cast<float>(maxPossibleValue)
        );
}

Item::~Item()
{
}

int Item::get()
{
    return this->value;
}

std::vector<std::string> Item::get_description_list()
{
    return this->descriptionList;
}

Potion::Potion(int uidNum, int tierNum, int maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
    std::stringstream stream;
    stream << "Heal a creature for " << this->value << " HP";
    this->descriptionList.emplace_back(stream.str());
}

Potion::~Potion()
{
}

Poison::Poison(int uidNum, int tierNum, int maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
    std::stringstream stream;
    stream << "Damage a creature for " << this->value << " HP";
    this->descriptionList.emplace_back(stream.str());
    this->descriptionList.emplace_back("Ignores defense");
}

Poison::~Poison()
{
}

Elixir::Elixir(int uidNum, int tierNum, int maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
    std::stringstream stream;
    stream << "Raise attack power of a creature by " << this->value;
    this->descriptionList.emplace_back(stream.str());
    this->descriptionList.emplace_back("Lasts until end of battle");
}

Elixir::~Elixir()
{
}

Revive::Revive(int uidNum, int tierNum, int maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
    this->descriptionList.emplace_back("Revive a creature with 0 HP");
}

Revive::~Revive()
{
}

Bait::Bait(int uidNum, int tierNum, int maxPossibleValue, bool isPersistent) :
Item(uidNum, tierNum, maxPossibleValue, isPersistent)
{
    std::stringstream stream;
    stream << "Raises chances of catching wild creature by " << this->value;
    this->descriptionList.emplace_back(stream.str());
    this->descriptionList.emplace_back("Lasts until end of battle");
}

Bait::~Bait()
{
}

};
