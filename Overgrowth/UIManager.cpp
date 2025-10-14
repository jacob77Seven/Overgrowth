#include "GameDefines.h"

#include "UIManager.h"
#include "Settings.h"
#include "ComponentIncludes.h"

void CUIManager::InitializeUI() {
	m_pRogueFrame.SetSprite((UINT)eSprite::RogueCharFrame, m_pRenderer);
	m_pWarriorFrame.SetSprite((UINT)eSprite::WarriorCharFrame, m_pRenderer);
	m_pDruidFrame.SetSprite((UINT)eSprite::DruidCharFrame, m_pRenderer);

	m_pRogueHealthbar.SetBackgroundSprite((UINT)eSprite::HealthbarBackground, m_pRenderer);
	m_pRogueHealthbar.SetHealthbarSprite((UINT)eSprite::Healthbar, m_pRenderer);
	m_pWarriorHealthbar.SetBackgroundSprite((UINT)eSprite::HealthbarBackground, m_pRenderer);
	m_pWarriorHealthbar.SetHealthbarSprite((UINT)eSprite::Healthbar, m_pRenderer);
	m_pDruidHealthbar.SetBackgroundSprite((UINT)eSprite::HealthbarBackground, m_pRenderer);
	m_pDruidHealthbar.SetHealthbarSprite((UINT)eSprite::Healthbar, m_pRenderer);

	SetActiveCharFrame(eInput::KeyOne);
	CalcHealthbarsTargets(eInput::KeyOne);
	MoveUI();
}

void CUIManager::Input(const eInput input) {
	if (m_pTimer->GetTime() - m_fCharSwitchTime > m_fCharSwitchCooldown)
		if (input == eInput::KeyOne || input == eInput::KeyTwo || input == eInput::KeyThree) {
			SetActiveCharFrame(input);
			CalcHealthbarsTargets(input);
			m_fCharSwitchTime = m_pTimer->GetTime();
		}
}

void CUIManager::MoveUI() {
	float m_fElapsedTime = m_pTimer->GetTime() - m_fCharSwitchTime;

	if (m_fElapsedTime > m_fCharSwitchCooldown) {
		m_pRogueFrame.SetToTargets();
		m_pWarriorFrame.SetToTargets();
		m_pDruidFrame.SetToTargets();

		m_pRogueHealthbar.SetToTargets();
		m_pWarriorHealthbar.SetToTargets();
		m_pDruidHealthbar.SetToTargets();
		return;
	}

	float t = m_fElapsedTime / m_fCharSwitchCooldown;

	m_pRogueFrame.InterpToTargets(t);
	m_pWarriorFrame.InterpToTargets(t);
	m_pDruidFrame.InterpToTargets(t);

	m_pRogueHealthbar.InterpToTargets(t);
	m_pWarriorHealthbar.InterpToTargets(t);
	m_pDruidHealthbar.InterpToTargets(t);
}

void CUIManager::SetActiveCharFrame(const eInput input) {
	switch (input) {
		case eInput::KeyOne:
			m_pRogueFrame.CalcTargetScale(m_fActiveFrameHeight);
			m_pWarriorFrame.CalcTargetScale(m_fInactiveFrameHeight);
			m_pDruidFrame.CalcTargetScale(m_fInactiveFrameHeight);
			break;
		case eInput::KeyTwo:
			m_pRogueFrame.CalcTargetScale(m_fInactiveFrameHeight);
			m_pWarriorFrame.CalcTargetScale(m_fActiveFrameHeight);
			m_pDruidFrame.CalcTargetScale(m_fInactiveFrameHeight);
			break;
		case eInput::KeyThree:
			m_pRogueFrame.CalcTargetScale(m_fInactiveFrameHeight);
			m_pWarriorFrame.CalcTargetScale(m_fInactiveFrameHeight);
			m_pDruidFrame.CalcTargetScale(m_fActiveFrameHeight);
			break;
	}

	m_pRogueFrame.CalcTargetPos((float)m_nWinHeight);
	m_pWarriorFrame.CalcTargetPos(m_pRogueFrame.m_fTargetPosY - m_pRogueFrame.m_fTargetPosX - m_fFrameOffset);
	m_pDruidFrame.CalcTargetPos(m_pWarriorFrame.m_fTargetPosY - m_pWarriorFrame.m_fTargetPosX - m_fFrameOffset);
}

void CUIManager::CalcHealthbarsTargets(const eInput input) {
	switch (input) {
		case eInput::KeyOne:
			m_pRogueHealthbar.CalcTargets(m_pRogueFrame.m_fTargetPosX, m_pRogueFrame.m_fTargetPosY, m_fActiveHealthbarWidth, m_fActiveHealthbarHeight);
			m_pWarriorHealthbar.CalcTargets(m_pWarriorFrame.m_fTargetPosX, m_pWarriorFrame.m_fTargetPosY, m_fInactiveHealthbarWidth, m_fInactiveHealthbarHeight);
			m_pDruidHealthbar.CalcTargets(m_pDruidFrame.m_fTargetPosX, m_pDruidFrame.m_fTargetPosY, m_fInactiveHealthbarWidth, m_fInactiveHealthbarHeight);
			break;
		case eInput::KeyTwo:
			m_pRogueHealthbar.CalcTargets(m_pRogueFrame.m_fTargetPosX, m_pRogueFrame.m_fTargetPosY, m_fInactiveHealthbarWidth, m_fInactiveHealthbarHeight);
			m_pWarriorHealthbar.CalcTargets(m_pWarriorFrame.m_fTargetPosX, m_pWarriorFrame.m_fTargetPosY, m_fActiveHealthbarWidth, m_fActiveHealthbarHeight);
			m_pDruidHealthbar.CalcTargets(m_pDruidFrame.m_fTargetPosX, m_pDruidFrame.m_fTargetPosY, m_fInactiveHealthbarWidth, m_fInactiveHealthbarHeight);
			break;
		case eInput::KeyThree:
			m_pRogueHealthbar.CalcTargets(m_pRogueFrame.m_fTargetPosX, m_pRogueFrame.m_fTargetPosY, m_fInactiveHealthbarWidth, m_fInactiveHealthbarHeight);
			m_pWarriorHealthbar.CalcTargets(m_pWarriorFrame.m_fTargetPosX, m_pWarriorFrame.m_fTargetPosY, m_fInactiveHealthbarWidth, m_fInactiveHealthbarHeight);
			m_pDruidHealthbar.CalcTargets(m_pDruidFrame.m_fTargetPosX, m_pDruidFrame.m_fTargetPosY, m_fActiveHealthbarWidth, m_fActiveHealthbarHeight);
			break;
	}
}

void CUIManager::DrawUI() {
	MoveUI();

	m_pRenderer->Draw(&m_pRogueFrame.GetSprite());
	m_pRenderer->Draw(&m_pWarriorFrame.GetSprite());
	m_pRenderer->Draw(&m_pDruidFrame.GetSprite());

	m_pRenderer->Draw(&m_pRogueHealthbar.GetBackgroundSprite());
	m_pRenderer->Draw(&m_pRogueHealthbar.GetHealthbarSprite());
	m_pRenderer->Draw(&m_pWarriorHealthbar.GetBackgroundSprite());
	m_pRenderer->Draw(&m_pWarriorHealthbar.GetHealthbarSprite());
	m_pRenderer->Draw(&m_pDruidHealthbar.GetBackgroundSprite());
	m_pRenderer->Draw(&m_pDruidHealthbar.GetHealthbarSprite());
}