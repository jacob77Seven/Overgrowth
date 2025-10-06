#include "GameDefines.h"

#include "UIManager.h"

void CUIManager::InitializeUI() {
	m_pRogueCharFrame.m_nSpriteIndex = (UINT)eSprite::RogueCharFrame;
}

void CUIManager::DrawUI() {
	m_pRenderer->Draw(&m_pRogueCharFrame);
}