#pragma once

#ifndef __L4RC_GAME_COMMON_H__
#define __L4RC_GAME_COMMON_H__

#include "SpriteRenderer.h"

// Forward declarations
class CUIManager;
class IInput;

class CCommon {
	protected:
		static LSpriteRenderer* m_pRenderer;
		static CUIManager* m_pUIManager;
		static LBaseCamera* m_pCamera;
		static std::vector<IInput*> m_pInputManager;

		static float m_fCameraPosZ;
};

#endif