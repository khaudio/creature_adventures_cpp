#ifndef CREATUREADVENTURES_ARTIFACT_H
#define CREATUREADVENTURES_ARTIFACT_H

#include "item.h"

namespace CreatureAdventures
{

/* Declarations */
class Artifact;

enum ArtifactIndex
{
    SIGILOFPOWER = 0,
    SIGILOFSPEED = 1,
    SIGILOFWISDOM = 2,
    QUIETSHOES = 3,
};

/* Artifacts award players special abilities.
Sigils are unique artifacts. */

class Artifact
{

public:

    /* Number of available Artifact types */
    static constexpr const int numTypes = 4;

    static constexpr const std::array<ArtifactIndex, Artifact::numTypes> types = {
            SIGILOFPOWER,
            SIGILOFSPEED,
            SIGILOFWISDOM,
            QUIETSHOES,
        };

    static constexpr const std::array<const char*, Artifact::numTypes> names = {
            "Sigil of Power",
            "Sigil of Speed",
            "Sigil of Wisdom",
            "Quiet Shoes",
        };

    static constexpr const std::array<const char*, Artifact::numTypes> descriptions = {
            "Add 3 attack points to a creature you control",
            "You may act first in battle.  After the first attack, all following attacks are simultaneous.",
            "Heal one creature for 50% max HP once per turn (or once per battle)",
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

};

#endif