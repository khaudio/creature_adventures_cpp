#include "sigil.h"

namespace CreatureAdventures
{

Artifact::Artifact(ArtifactIndex typeIndex) :
type(typeIndex)
{
}

Artifact::Artifact(const Artifact& ref) :
type(ref.type)
{
}

Artifact::~Artifact()
{
}

Sigil::Sigil(SigilIndex typeIndex) :
type(typeIndex)
{
}

Sigil::Sigil(const Sigil& ref) :
type(ref.type)
{
}

Sigil::~Sigil()
{
}

};
