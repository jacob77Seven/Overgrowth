#pragma once

#ifndef __L4RC_GAME_COMMON_H__
#define __L4RC_GAME_COMMON_H__

#include "GameDefines.h"
#include "SpriteRenderer.h"

class CUIManager;

class CCommon {
	protected:
		static LSpriteRenderer* m_pRenderer;
		static CUIManager* m_pUIManager;
};

#endif