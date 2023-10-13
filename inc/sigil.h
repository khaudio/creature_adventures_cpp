#ifndef CREATUREADVENTURES_SIGIL_H
#define CREATUREADVENTURES_SIGIL_H

#include "item.h"

namespace CreatureAdventures
{

class Artifact;
class Sigil;
class SigilOfPower;
class SigilOfSpeed;
class SigilOfWisdom;
class QuietShoes;

class Artifact
{

public:

    Artifact();
    Artifact(const Artifact& ref);

    ~Artifact();

};

class Sigil
{

public:

    Sigil();
    Sigil(const Sigil& ref);

    ~Sigil();

};

class SigilOfPower : public Sigil
{

public:

    static constexpr const char* name = "Sigil of Power";
    static constexpr const char* description = "Add 3 attack points to a creature you control";

    SigilOfPower();
    SigilOfPower(const SigilOfPower& ref);

    ~SigilOfPower();

};

class SigilOfSpeed : public Sigil
{

public:

    static constexpr const char* name = "Sigil of Speed";
    static constexpr const char* description = "You may act first in battle.  After the first attack, all following attacks are simultaneous.";

    SigilOfSpeed();
    SigilOfSpeed(const SigilOfSpeed& ref);

    ~SigilOfSpeed();

};

class SigilOfWisdom : public Sigil
{

public:

    static constexpr const char* name = "Sigil of Wisdom";
    static constexpr const char* description = "Heal one creature for 50% max HP once per turn (or once per battle)";

    SigilOfWisdom();
    SigilOfWisdom(const SigilOfWisdom& ref);

    ~SigilOfWisdom();

};

class QuietShoes : public Artifact
{

public:

    static constexpr const char* name = "Quiet Shoes";
    static constexpr const char* description = "Allows a player to avoid battles with wild creatures";

    QuietShoes();
    QuietShoes(const QuietShoes& ref);

    ~QuietShoes();

};

};

#endif