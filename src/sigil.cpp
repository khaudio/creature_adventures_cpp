#include "sigil.h"

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

Sigil::Sigil(SigilIndex typeIndex) :
type(typeIndex)
{
    #if _DEBUG
    _validate_type();
    #endif
}

Sigil::Sigil(const Sigil& ref) :
type(ref.type)
{
    #if _DEBUG
    _validate_type();
    #endif
}

Sigil::~Sigil()
{
}

void Sigil::_validate_type()
{
    auto iter = std::find(
            Sigil::types.begin(),
            Sigil::types.end(),
            this->type
        );
    if (iter == types.end())
    {
        throw std::out_of_range("Sigil type index not found");
    }
}

};
