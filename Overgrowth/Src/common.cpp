/// \file Common.cpp
/// \brief Code for the class OCommon.
///
/// This file contains declarations and initial values
/// for OCommon's static member variables.

#include "Common.h"

LSpriteRenderer* OCommon::m_pRenderer = nullptr;
OObjectManager* OCommon::m_pObjectManager = nullptr;
LParticleEngine2D* OCommon::m_pParticleEngine = nullptr;
CTileManager* OCommon::m_pTileManager = nullptr;

bool OCommon::m_bDrawAABBs = false;
bool OCommon::m_bGodMode = false;

Vector2 OCommon::m_vWorldSize = Vector2::Zero;
CPlayer* OCommon::m_pPlayer = nullptr;
