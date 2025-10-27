#include "BaseLevelAsset.h"

OBaseLevelAsset::OBaseLevelAsset(const Vector3& p)
{
    m_vPos = p; // inherited from OObject
}

OBaseLevelAsset::~OBaseLevelAsset()
{
}

void OBaseLevelAsset::OnDestroy()
{
    OObject::OnDestroy();
}

void OBaseLevelAsset::BeginPlay()
{
	OObject::BeginPlay();
}
