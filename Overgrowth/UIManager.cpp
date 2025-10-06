#include "GameDefines.h"

#include "UIManager.h"
#include "Settings.h"

void CUIManager::InitializeUI() {
	m_pRogueCharFrame.m_nSpriteIndex = (UINT)eSprite::RogueCharFrame;
	m_pWarriorCharFrame.m_nSpriteIndex = (UINT)eSprite::WarriorCharFrame;
	m_pDruidCharFrame.m_nSpriteIndex = (UINT)eSprite::DruidCharFrame;

	m_pRenderer->GetSize(eSprite::RogueCharFrame, m_vRogueCharFrameSize.x, m_vRogueCharFrameSize.y);
	m_pRenderer->GetSize(eSprite::WarriorCharFrame, m_vWarriorCharFrameSize.x, m_vWarriorCharFrameSize.y);
	m_pRenderer->GetSize(eSprite::DruidCharFrame, m_vDruidCharFrameSize.x, m_vDruidCharFrameSize.y);

	m_pRogueCharFrame.m_vPos = m_vWinCenter - Vector2(400.f, 0.f);
	m_pWarriorCharFrame.m_vPos = m_vWinCenter;
	m_pDruidCharFrame.m_vPos = m_vWinCenter + Vector2(400.f, 0.f);

	ActiveCharFrame((UINT)eSprite::RogueCharFrame);
}

void CUIManager::PositionCharFrames() {
	Vector2 pos;

	pos.y = m_nWinHeight - (m_vRogueCharFrameSize.y * m_pRogueCharFrame.m_fYScale / 2);
	pos.x = m_vRogueCharFrameSize.x * m_pRogueCharFrame.m_fXScale / 2;
	m_pRogueCharFrame.m_vPos = pos;

	pos.y = pos.y - pos.x - offset - (m_vWarriorCharFrameSize.y * m_pWarriorCharFrame.m_fYScale / 2);
	pos.x = m_vWarriorCharFrameSize.x * m_pWarriorCharFrame.m_fXScale / 2;
	m_pWarriorCharFrame.m_vPos = pos;

	pos.y = pos.y - pos.x - offset - (m_vDruidCharFrameSize.y * m_pDruidCharFrame.m_fYScale / 2);
	pos.x = m_vDruidCharFrameSize.x * m_pDruidCharFrame.m_fXScale / 2;
	m_pDruidCharFrame.m_vPos = pos;
}

void CUIManager::ActiveCharFrame(UINT c) {
	switch (c) {
		case (UINT)eSprite::RogueCharFrame:
			m_pRogueCharFrame.m_fXScale = 1 / (m_vRogueCharFrameSize.x / m_fActiveHeight);
			m_pRogueCharFrame.m_fYScale = 1 / (m_vRogueCharFrameSize.y / m_fActiveHeight);
			
			InactiveCharFrame((UINT)eSprite::WarriorCharFrame);
			InactiveCharFrame((UINT)eSprite::DruidCharFrame);
			break;
		case (UINT)eSprite::WarriorCharFrame:
			m_pWarriorCharFrame.m_fXScale = 1 / (m_vWarriorCharFrameSize.x / m_fActiveHeight);
			m_pWarriorCharFrame.m_fYScale = 1 / (m_vWarriorCharFrameSize.y / m_fActiveHeight);

			InactiveCharFrame((UINT)eSprite::RogueCharFrame);
			InactiveCharFrame((UINT)eSprite::DruidCharFrame);
			break;
		case (UINT)eSprite::DruidCharFrame:
			m_pDruidCharFrame.m_fXScale = 1 / (m_vDruidCharFrameSize.x / m_fActiveHeight);
			m_pDruidCharFrame.m_fYScale = 1 / (m_vDruidCharFrameSize.y / m_fActiveHeight);

			InactiveCharFrame((UINT)eSprite::RogueCharFrame);
			InactiveCharFrame((UINT)eSprite::WarriorCharFrame);
			break;
	}

	PositionCharFrames();
}

void CUIManager::InactiveCharFrame(UINT c) {
	switch (c) {
		case (UINT)eSprite::RogueCharFrame:
			m_pRogueCharFrame.m_fXScale = 1 / (m_vRogueCharFrameSize.x / m_fInactiveHeight);
			m_pRogueCharFrame.m_fYScale = 1 / (m_vRogueCharFrameSize.y / m_fInactiveHeight);
			break;
		case (UINT)eSprite::WarriorCharFrame:
			m_pWarriorCharFrame.m_fXScale = 1 / (m_vWarriorCharFrameSize.x / m_fInactiveHeight);
			m_pWarriorCharFrame.m_fYScale = 1 / (m_vWarriorCharFrameSize.y / m_fInactiveHeight);
			break;
		case (UINT)eSprite::DruidCharFrame:
			m_pDruidCharFrame.m_fXScale = 1 / (m_vDruidCharFrameSize.x / m_fInactiveHeight);
			m_pDruidCharFrame.m_fYScale = 1 / (m_vDruidCharFrameSize.y / m_fInactiveHeight);
			break;
	}
}

void CUIManager::DrawUI() {
	m_pRenderer->Draw(&m_pRogueCharFrame);
	m_pRenderer->Draw(&m_pWarriorCharFrame);
	m_pRenderer->Draw(&m_pDruidCharFrame);
}