#include "GameDefines.h"

#include "UIManager.h"
#include "Settings.h"
#include "ComponentIncludes.h"

void CUIManager::InitializeUI() {
	m_pRogueFrame.m_nSpriteIndex = (UINT)eSprite::RogueCharFrame;
	m_pWarriorFrame.m_nSpriteIndex = (UINT)eSprite::WarriorCharFrame;
	m_pDruidFrame.m_nSpriteIndex = (UINT)eSprite::DruidCharFrame;

	m_pRenderer->GetSize(eSprite::RogueCharFrame, m_vRogueSpriteSize.x, m_vRogueSpriteSize.y);
	m_pRenderer->GetSize(eSprite::WarriorCharFrame, m_vWarriorSpriteSize.x, m_vWarriorSpriteSize.y);
	m_pRenderer->GetSize(eSprite::DruidCharFrame, m_vDruidSpriteSize.x, m_vDruidSpriteSize.y);

	ActiveCharFrame((UINT)eSprite::RogueCharFrame);

	m_fCharSwitchTime = -1.0f;
}

void CUIManager::CalcTargetPos() {
	m_vTargetRogueFramePos.x = m_vRogueSpriteSize.x * m_vTargetRogueFrameScale.x / 2;
	m_vTargetRogueFramePos.y = m_nWinHeight - (m_vRogueSpriteSize.y * m_vTargetRogueFrameScale.y / 2);

	m_vTargetWarriorFramePos.x = m_vWarriorSpriteSize.x * m_vTargetWarriorFrameScale.x / 2;
	m_vTargetWarriorFramePos.y = m_vTargetRogueFramePos.y - m_vTargetRogueFramePos.x - m_fOffset - (m_vWarriorSpriteSize.y * m_vTargetWarriorFrameScale.y / 2);

	m_vTargetDruidFramePos.x = m_vDruidSpriteSize.x * m_vTargetDruidFrameScale.x / 2;
	m_vTargetDruidFramePos.y = m_vTargetWarriorFramePos.y - m_vTargetWarriorFramePos.x - m_fOffset - (m_vDruidSpriteSize.y * m_vTargetDruidFrameScale.y / 2);

	m_fCharSwitchTime = m_pTimer->GetTime();
}

void CUIManager::MoveCharFrames() {
	float m_fElapsedTime = m_pTimer->GetTime() - m_fCharSwitchTime;

	if (m_fElapsedTime > m_fCharSwitchCooldown) {
		m_pRogueFrame.m_vPos = m_vTargetRogueFramePos;
		m_pWarriorFrame.m_vPos = m_vTargetWarriorFramePos;
		m_pDruidFrame.m_vPos = m_vTargetDruidFramePos;

		m_pRogueFrame.m_fXScale = m_vTargetRogueFrameScale.x;
		m_pRogueFrame.m_fYScale = m_vTargetRogueFrameScale.y;

		m_pWarriorFrame.m_fXScale = m_vTargetWarriorFrameScale.x;
		m_pWarriorFrame.m_fYScale = m_vTargetWarriorFrameScale.y;

		m_pDruidFrame.m_fXScale = m_vTargetDruidFrameScale.x;
		m_pDruidFrame.m_fYScale = m_vTargetDruidFrameScale.y;
		return;
	}

	float t = m_fElapsedTime / m_fCharSwitchCooldown;

	m_pRogueFrame.m_vPos.x = m_pRogueFrame.m_vPos.x + (m_vTargetRogueFramePos.x - m_pRogueFrame.m_vPos.x) * t;
	m_pRogueFrame.m_vPos.y = m_pRogueFrame.m_vPos.y + (m_vTargetRogueFramePos.y - m_pRogueFrame.m_vPos.y) * t;
	m_pRogueFrame.m_fXScale = m_pRogueFrame.m_fXScale + (m_vTargetRogueFrameScale.x - m_pRogueFrame.m_fXScale) * t;
	m_pRogueFrame.m_fYScale = m_pRogueFrame.m_fYScale + (m_vTargetRogueFrameScale.y - m_pRogueFrame.m_fYScale) * t;

	m_pWarriorFrame.m_vPos.x = m_pWarriorFrame.m_vPos.x + (m_vTargetWarriorFramePos.x - m_pWarriorFrame.m_vPos.x) * t;
	m_pWarriorFrame.m_vPos.y = m_pWarriorFrame.m_vPos.y + (m_vTargetWarriorFramePos.y - m_pWarriorFrame.m_vPos.y) * t;
	m_pWarriorFrame.m_fXScale = m_pWarriorFrame.m_fXScale + (m_vTargetWarriorFrameScale.x - m_pWarriorFrame.m_fXScale) * t;
	m_pWarriorFrame.m_fYScale = m_pWarriorFrame.m_fYScale + (m_vTargetWarriorFrameScale.y - m_pWarriorFrame.m_fYScale) * t;

	m_pDruidFrame.m_vPos.x = m_pDruidFrame.m_vPos.x + (m_vTargetDruidFramePos.x - m_pDruidFrame.m_vPos.x) * t;
	m_pDruidFrame.m_vPos.y = m_pDruidFrame.m_vPos.y + (m_vTargetDruidFramePos.y - m_pDruidFrame.m_vPos.y) * t;
	m_pDruidFrame.m_fXScale = m_pDruidFrame.m_fXScale + (m_vTargetDruidFrameScale.x - m_pDruidFrame.m_fXScale) * t;
	m_pDruidFrame.m_fYScale = m_pDruidFrame.m_fYScale + (m_vTargetDruidFrameScale.y - m_pDruidFrame.m_fYScale) * t;
}

void CUIManager::ActiveCharFrame(UINT c) {
	switch (c) {
		case (UINT)eSprite::RogueCharFrame:
			m_vTargetRogueFrameScale.x = 1 / (m_vRogueSpriteSize.x / m_fActiveHeight);
			m_vTargetRogueFrameScale.y = 1 / (m_vRogueSpriteSize.y / m_fActiveHeight);
			
			InactiveCharFrame((UINT)eSprite::WarriorCharFrame);
			InactiveCharFrame((UINT)eSprite::DruidCharFrame);
			break;
		case (UINT)eSprite::WarriorCharFrame:
			m_vTargetWarriorFrameScale.x = 1 / (m_vWarriorSpriteSize.x / m_fActiveHeight);
			m_vTargetWarriorFrameScale.y = 1 / (m_vWarriorSpriteSize.y / m_fActiveHeight);

			InactiveCharFrame((UINT)eSprite::RogueCharFrame);
			InactiveCharFrame((UINT)eSprite::DruidCharFrame);
			break;
		case (UINT)eSprite::DruidCharFrame:
			m_vTargetDruidFrameScale.x = 1 / (m_vDruidSpriteSize.x / m_fActiveHeight);
			m_vTargetDruidFrameScale.y = 1 / (m_vDruidSpriteSize.y / m_fActiveHeight);

			InactiveCharFrame((UINT)eSprite::RogueCharFrame);
			InactiveCharFrame((UINT)eSprite::WarriorCharFrame);
			break;
	}

	CalcTargetPos();
}

void CUIManager::InactiveCharFrame(UINT c) {
	switch (c) {
		case (UINT)eSprite::RogueCharFrame:
			m_vTargetRogueFrameScale.x = 1 / (m_vRogueSpriteSize.x / m_fInactiveHeight);
			m_vTargetRogueFrameScale.y = 1 / (m_vRogueSpriteSize.y / m_fInactiveHeight);
			break;
		case (UINT)eSprite::WarriorCharFrame:
			m_vTargetWarriorFrameScale.x = 1 / (m_vWarriorSpriteSize.x / m_fInactiveHeight);
			m_vTargetWarriorFrameScale.y = 1 / (m_vWarriorSpriteSize.y / m_fInactiveHeight);
			break;
		case (UINT)eSprite::DruidCharFrame:
			m_vTargetDruidFrameScale.x = 1 / (m_vDruidSpriteSize.x / m_fInactiveHeight);
			m_vTargetDruidFrameScale.y = 1 / (m_vDruidSpriteSize.y / m_fInactiveHeight);
			break;
	}
}

void CUIManager::DrawUI() {
	MoveCharFrames();

	m_pRenderer->Draw(&m_pRogueFrame);
	m_pRenderer->Draw(&m_pWarriorFrame);
	m_pRenderer->Draw(&m_pDruidFrame);
}