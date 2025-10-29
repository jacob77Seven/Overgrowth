#include "BaseLevelAsset.h"

BaseLevelAsset::BaseLevelAsset(const Vector3& p)
{
    m_vPos = p; // inherited from OObject
}

BaseLevelAsset::~BaseLevelAsset()
{
}

void BaseLevelAsset::OnDestroy()
{
    OObject::OnDestroy();
}

void BaseLevelAsset::BeginPlay()
{
	OObject::BeginPlay();
}
