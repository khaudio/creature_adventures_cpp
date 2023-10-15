#include "sigil.h"

namespace CreatureAdventures
{

Artifact::Artifact() :
typeIndex(Artifact::staticTypeIndex)
{
}

Artifact::Artifact(const Artifact& ref) :
typeIndex(ref.typeIndex)
{
}

Artifact::~Artifact()
{
}

Sigil::Sigil() :
typeIndex(Sigil::staticTypeIndex)
{
}

Sigil::Sigil(const Sigil& ref) :
typeIndex(ref.typeIndex)
{
}

Sigil::~Sigil()
{
}

SigilOfPower::SigilOfPower() :
Sigil()
{
    this->typeIndex = SigilOfPower::staticTypeIndex;
}

SigilOfPower::SigilOfPower(const SigilOfPower& ref) :
Sigil(ref)
{
}

SigilOfPower::~SigilOfPower()
{
}

SigilOfSpeed::SigilOfSpeed() :
Sigil()
{
    this->typeIndex = SigilOfSpeed::staticTypeIndex;
}

SigilOfSpeed::SigilOfSpeed(const SigilOfSpeed& ref) :
Sigil(ref)
{
}

SigilOfSpeed::~SigilOfSpeed()
{
}

SigilOfWisdom::SigilOfWisdom() :
Sigil()
{
    this->typeIndex = SigilOfWisdom::staticTypeIndex;
}

SigilOfWisdom::SigilOfWisdom(const SigilOfWisdom& ref) :
Sigil(ref)
{
}

SigilOfWisdom::~SigilOfWisdom()
{
}

QuietShoes::QuietShoes() :
Artifact()
{
    this->typeIndex = QuietShoes::staticTypeIndex;
}

QuietShoes::QuietShoes(const QuietShoes& ref) :
Artifact(ref)
{
}

QuietShoes::~QuietShoes()
{
}

};
