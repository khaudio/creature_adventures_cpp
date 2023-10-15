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

    /* Artifact name */
    static constexpr const char* name = "";

    /* Artifact description */
    static constexpr const char* description = "";

    /* Number of available Artifact types */
    static constexpr const int numTypes = 1;

    /* Class type index */
    static constexpr const int staticTypeIndex = -1;

public:

    /* Artifact type index */
    int typeIndex;

public:

    Artifact();
    Artifact(const Artifact& ref);

    ~Artifact();

};

class Sigil
{

public:

    /* Sigil name */
    static constexpr const char* name = "";

    /* Sigil description */
    static constexpr const char* description = "";

    /* Number of available Sigil types */
    static constexpr const int numTypes = 3;

    /* Class type index */
    static constexpr const int staticTypeIndex = -1;

public:

    /* Sigil type index */
    int typeIndex;

public:

    Sigil();
    Sigil(const Sigil& ref);

    ~Sigil();

};

class SigilOfPower : public Sigil
{

public:

    /* Sigil name */
    static constexpr const char* name = "Sigil of Power";

    /* Sigil description */
    static constexpr const char* description = "Add 3 attack points to a creature you control";

    /* Class type index */
    static constexpr const int staticTypeIndex = 0;

public:

    SigilOfPower();
    SigilOfPower(const SigilOfPower& ref);

    ~SigilOfPower();

};

class SigilOfSpeed : public Sigil
{

public:

    /* Sigil name */
    static constexpr const char* name = "Sigil of Speed";

    /* Sigil description */
    static constexpr const char* description = "You may act first in battle.  After the first attack, all following attacks are simultaneous.";

    /* Class type index */
    static constexpr const int staticTypeIndex = 1;

    SigilOfSpeed();
    SigilOfSpeed(const SigilOfSpeed& ref);

    ~SigilOfSpeed();

};

class SigilOfWisdom : public Sigil
{

public:

    /* Sigil name */
    static constexpr const char* name = "Sigil of Wisdom";

    /* Sigil description */
    static constexpr const char* description = "Heal one creature for 50% max HP once per turn (or once per battle)";

    /* Class type index */
    static constexpr const int staticTypeIndex = 2;

    SigilOfWisdom();
    SigilOfWisdom(const SigilOfWisdom& ref);

    ~SigilOfWisdom();

};

class QuietShoes : public Artifact
{

public:

    /* Artifact name */
    static constexpr const char* name = "Quiet Shoes";

    /* Artifact description */
    static constexpr const char* description = "Allows a player to avoid battles with wild creatures";

    /* Class type index */
    static constexpr const int staticTypeIndex = 0;

    QuietShoes();
    QuietShoes(const QuietShoes& ref);

    ~QuietShoes();

};

};

#endif