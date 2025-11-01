/// \file Common.cpp
/// \brief Code for the class OCommon.
///
/// This file contains declarations and initial values
/// for OCommon's static member variables.

#include "Common.h"

ORenderer* OCommon::m_pRenderer = nullptr;
OObjectManager* OCommon::m_pObjectManager = nullptr;
LParticleEngine2D* OCommon::m_pParticleEngine = nullptr;
CTileManager* OCommon::m_pTileManager = nullptr;
LBaseCamera* OCommon::m_pCamera = nullptr;
CUIManager* OCommon::m_pUIManager = nullptr;
std::vector<IInput*> OCommon::m_pInputManager;
PlayerManager* OCommon::m_pPlayerManager = nullptr;

bool OCommon::m_bDrawAABBs = false;
bool OCommon::m_bGodMode = false;

Vector2 OCommon::m_vWorldSize = Vector2::Zero;
CPlayer* OCommon::m_pPlayer = nullptr;
float OCommon::m_fTile = 1000.f;

float OCommon::m_fCameraPosZ = -1000.0f;

UINT OCommon::GetSpriteHandleIndex(const std::string handle) {
    for (UINT i = 0; i < (UINT)eSprite::Size; i++) {
        if (OAssetDefines::spriteHandles[i] == handle)
            return i;
    }
    return -1;
}

UINT OCommon::GetSoundHandleIndex(const std::string handle) {
    for (UINT i = 0; i < (UINT)eSound::Size; i++) {
        if (OAssetDefines::soundHandles[i] == handle)
            return i;
    }
    return -1;
}