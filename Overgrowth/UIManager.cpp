#include "GameDefines.h"

#include "UIManager.h"
#include "Settings.h"
#include "ComponentIncludes.h"

void CUIManager::InitializeUI() {
	m_pRogueFrame.SetSprite((UINT)eSprite::RogueCharFrame, m_pRenderer);
	m_pWarrior.SetSprite((UINT)eSprite::WarriorCharFrame, m_pRenderer);
	m_pDruid.SetSprite((UINT)eSprite::DruidCharFrame, m_pRenderer);

	SetActiveCharFrame((UINT)eSprite::RogueCharFrame);

	m_fCharSwitchTime = -1.0f;
}

void CUIManager::CalcFramesTargetPos() {
	m_pRogueFrame.CalcTargetPos(m_nWinHeight);
	m_pWarrior.CalcTargetPos(m_pRogueFrame.m_fTargetPosY - m_pRogueFrame.m_fTargetPosX - m_fOffset);
	m_pDruid.CalcTargetPos(m_pWarrior.m_fTargetPosY - m_pWarrior.m_fTargetPosX - m_fOffset);

	m_fCharSwitchTime = m_pTimer->GetTime();
}

void CUIManager::MoveFrames() {
	float m_fElapsedTime = m_pTimer->GetTime() - m_fCharSwitchTime;

	if (m_fElapsedTime > m_fCharSwitchCooldown) {
		m_pRogueFrame.SetToTargets();
		m_pWarrior.SetToTargets();
		m_pDruid.SetToTargets();
		return;
	}

	float t = m_fElapsedTime / m_fCharSwitchCooldown;

	m_pRogueFrame.InterpToTargets(t);
	m_pWarrior.InterpToTargets(t);
	m_pDruid.InterpToTargets(t);
}

void CUIManager::SetActiveCharFrame(UINT c) {
	switch (c) {
		case (UINT)eSprite::RogueCharFrame:
			m_pRogueFrame.CalcTargetScale(m_fActiveHeight);
			m_pWarrior.CalcTargetScale(m_fInactiveHeight);
			m_pDruid.CalcTargetScale(m_fInactiveHeight);
			break;
		case (UINT)eSprite::WarriorCharFrame:
			m_pRogueFrame.CalcTargetScale(m_fInactiveHeight);
			m_pWarrior.CalcTargetScale(m_fActiveHeight);
			m_pDruid.CalcTargetScale(m_fInactiveHeight);
			break;
		case (UINT)eSprite::DruidCharFrame:
			m_pRogueFrame.CalcTargetScale(m_fInactiveHeight);
			m_pWarrior.CalcTargetScale(m_fInactiveHeight);
			m_pDruid.CalcTargetScale(m_fActiveHeight);
			break;
	}

	CalcFramesTargetPos();
}

void CUIManager::DrawUI() {
	MoveFrames();

	m_pRenderer->Draw(&m_pRogueFrame.GetSprite());
	m_pRenderer->Draw(&m_pWarrior.GetSprite());
	m_pRenderer->Draw(&m_pDruid.GetSprite());
}