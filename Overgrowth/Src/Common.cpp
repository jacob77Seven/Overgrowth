#include "Common.h"

ORenderer* OCommon::m_pRenderer = nullptr;
OObjectManager* OCommon::m_pObjectManager = nullptr;
LParticleEngine2D* OCommon::m_pParticleEngine = nullptr;
CTileManager* OCommon::m_pTileManager = nullptr;
CUIManager* OCommon::m_pUIManager = nullptr;
std::vector<IInput*> OCommon::m_pInputManager;

bool OCommon::m_bDrawAABBs = false;
bool OCommon::m_bGodMode = false;

Vector2 OCommon::m_vWorldSize = Vector2::Zero;
CPlayer* OCommon::m_pPlayer = nullptr;
float OCommon::m_fTile = 1000.f;

float OCommon::m_fCameraPosZ = -2400.0f;