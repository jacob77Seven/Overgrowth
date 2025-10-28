#include "Common.h"

LSpriteRenderer* CCommon::m_pRenderer = nullptr;
CUIManager* CCommon::m_pUIManager = nullptr;
LBaseCamera* CCommon::m_pCamera = nullptr;
std::vector<IInput*> CCommon::m_pInputManager;

float CCommon::m_fCameraPosZ = -1000.0f;