#include "artifact.h"

namespace CreatureAdventures
{

Artifact::Artifact(ArtifactIndex typeIndex) :
type(typeIndex)
{
    #if _DEBUG
    _validate_type();
    #endif
}

Artifact::Artifact(const Artifact& ref) :
type(ref.type)
{
    #if _DEBUG
    _validate_type();
    #endif
}

Artifact::~Artifact()
{
}

void Artifact::_validate_type()
{
    auto iter = std::find(
            Artifact::types.begin(),
            Artifact::types.end(),
            this->type
        );
    if (iter == types.end())
    {
        throw std::out_of_range("Artifact type index not found");
    }
}

};
