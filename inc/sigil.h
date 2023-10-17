#ifndef CREATUREADVENTURES_SIGIL_H
#define CREATUREADVENTURES_SIGIL_H

#include "item.h"

namespace CreatureAdventures
{

/* Declarations */
class Artifact;
class Sigil;

enum ArtifactIndex
{
    QUIETSHOES = 0,
};

enum SigilIndex
{
    SIGILOFPOWER = 0,
    SIGILOFSPEED = 1,
    SIGILOFWISDOM = 2,
};

class Artifact
{

public:

    /* Number of available Artifact types */
    static constexpr const int numTypes = 1;

    static constexpr const std::array<ArtifactIndex, Artifact::numTypes> types = {
            QUIETSHOES,
        };

    static constexpr const std::array<const char*, Artifact::numTypes> names = {
            "Quiet Shoes",
        };

    static constexpr const std::array<const char*, Artifact::numTypes> descriptions = {
            "Allows a player to avoid battles with wild creatures",
        };

    /* Artifact name */
    static constexpr const char* name = "";

    /* Artifact description */
    static constexpr const char* description = "";

public:

    /* Artifact type index */
    int type;

public:

    Artifact(ArtifactIndex typeIndex);
    Artifact(const Artifact& ref);

    ~Artifact();

protected:

    /* Enforce that type is valid */
    void _validate_type();

};

class Sigil
{

public:

    /* Number of available Sigil types */
    static constexpr const int numTypes = 3;

    static constexpr const std::array<SigilIndex, Sigil::numTypes> types = {
            SIGILOFPOWER,
            SIGILOFSPEED,
            SIGILOFWISDOM,
        };

    static constexpr const std::array<const char*, Sigil::numTypes> names = {
            "Sigil of Power",
            "Sigil of Speed",
            "Sigil of Wisdom",
        };

    static constexpr const std::array<const char*, Sigil::numTypes> descriptions = {
            "Add 3 attack points to a creature you control",
            "You may act first in battle.  After the first attack, all following attacks are simultaneous.",
            "Heal one creature for 50% max HP once per turn (or once per battle)",
        };

    /* Sigil name */
    static constexpr const char* name = "";

    /* Sigil description */
    static constexpr const char* description = "";

public:

    /* Sigil type index */
    int type;

public:

    Sigil(SigilIndex typeIndex);
    Sigil(const Sigil& ref);

    ~Sigil();

protected:

    /* Enforce that type is valid */
    void _validate_type();

};

};

#endif