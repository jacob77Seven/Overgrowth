#include "../GameDefines.h"

#include "UIManager.h"
#include "Settings.h"
#include "ComponentIncludes.h"

void CUIManager::InitializeUI() {
	m_pRogueFrame.SetSprite((UINT)eSprite::RogueCharFrame, m_pRenderer);
	m_pWarriorFrame.SetSprite((UINT)eSprite::WarriorCharFrame, m_pRenderer);
	m_pDruidFrame.SetSprite((UINT)eSprite::DruidCharFrame, m_pRenderer);

	m_pRogueHealthbar.SetBackgroundSprite((UINT)eSprite::HealthbarBackground, m_pRenderer);
	m_pRogueHealthbar.SetBarSprite((UINT)eSprite::Healthbar, m_pRenderer);

	m_pWarriorHealthbar.SetBackgroundSprite((UINT)eSprite::HealthbarBackground, m_pRenderer);
	m_pWarriorHealthbar.SetBarSprite((UINT)eSprite::Healthbar, m_pRenderer);

	m_pDruidHealthbar.SetBackgroundSprite((UINT)eSprite::HealthbarBackground, m_pRenderer);
	m_pDruidHealthbar.SetBarSprite((UINT)eSprite::Healthbar, m_pRenderer);

	m_pDruidManabar.SetBackgroundSprite((UINT)eSprite::ManabarBackground, m_pRenderer);
	m_pDruidManabar.SetBarSprite((UINT)eSprite::Manabar, m_pRenderer);

	m_pRogueAbilityOne.SetBackgroundSprite((UINT)eSprite::RogueAbilityOne, m_pRenderer);
	m_pRogueAbilityOne.SetBarSprite((UINT)eSprite::AbilityCooldown, m_pRenderer);
	m_pRogueAbilityTwo.SetBackgroundSprite((UINT)eSprite::RogueAbilityTwo, m_pRenderer);
	m_pRogueAbilityTwo.SetBarSprite((UINT)eSprite::AbilityCooldown, m_pRenderer);
	m_pRogueAbilityThree.SetBackgroundSprite((UINT)eSprite::RogueAbilityThree, m_pRenderer);
	m_pRogueAbilityThree.SetBarSprite((UINT)eSprite::AbilityCooldown, m_pRenderer);

	m_pWarriorAbilityOne.SetBackgroundSprite((UINT)eSprite::WarriorAbilityOne, m_pRenderer);
	m_pWarriorAbilityOne.SetBarSprite((UINT)eSprite::AbilityCooldown, m_pRenderer);
	m_pWarriorAbilityTwo.SetBackgroundSprite((UINT)eSprite::WarriorAbilityTwo, m_pRenderer);
	m_pWarriorAbilityTwo.SetBarSprite((UINT)eSprite::AbilityCooldown, m_pRenderer);
	m_pWarriorAbilityThree.SetBackgroundSprite((UINT)eSprite::WarriorAbilityThree, m_pRenderer);
	m_pWarriorAbilityThree.SetBarSprite((UINT)eSprite::AbilityCooldown, m_pRenderer);

	m_pDruidAbilityOne.SetBackgroundSprite((UINT)eSprite::DruidAbilityOne, m_pRenderer);
	m_pDruidAbilityOne.SetBarSprite((UINT)eSprite::AbilityCooldown, m_pRenderer);
	m_pDruidAbilityTwo.SetBackgroundSprite((UINT)eSprite::DruidAbilityTwo, m_pRenderer);
	m_pDruidAbilityTwo.SetBarSprite((UINT)eSprite::AbilityCooldown, m_pRenderer);
	m_pDruidAbilityThree.SetBackgroundSprite((UINT)eSprite::DruidAbilityThree, m_pRenderer);
	m_pDruidAbilityThree.SetBarSprite((UINT)eSprite::AbilityCooldown, m_pRenderer);

	charSelected = eCharSelected::Rogue;

	CalcFrameTargets();
	CalcHealthbarsTargets();
	CalcAbilitiesTargets();
	MoveUI();
}

void CUIManager::Input(const eInput& input) {
	float currentTime = m_pTimer->GetTime();

	if (currentTime - m_fCharSwitchTime > m_fCharSwitchCooldown) {
		switch (input) {
		case eInput::KeyOne:
			charSelected = eCharSelected::Rogue;
			CalcFrameTargets();
			CalcHealthbarsTargets();
			m_fCharSwitchTime = m_pTimer->GetTime();
			break;
		case eInput::KeyTwo:
			charSelected = eCharSelected::Warrior;
			CalcFrameTargets();
			CalcHealthbarsTargets();
			m_fCharSwitchTime = m_pTimer->GetTime();
			break;
		case eInput::KeyThree:
			charSelected = eCharSelected::Druid;
			CalcFrameTargets();
			CalcHealthbarsTargets();
			m_fCharSwitchTime = m_pTimer->GetTime();
			break;
		}
	}

	if (input == eInput::KeyQ) {
		switch (charSelected) {
		case eCharSelected::Rogue:
			if (currentTime - m_pRogueAbilityOne.GetPressedTime() > m_fAbilityCooldown) {
				m_pRogueAbilityOne.AbilityPressed(m_pTimer->GetTime(), m_fAbilityCooldown);
			}
			break;
		case eCharSelected::Warrior:
			if (currentTime - m_pWarriorAbilityOne.GetPressedTime() > m_fAbilityCooldown) {
				m_pWarriorAbilityOne.AbilityPressed(m_pTimer->GetTime(), m_fAbilityCooldown);
			}
			break;
		case eCharSelected::Druid:
			if (currentTime - m_pDruidAbilityOne.GetPressedTime() > m_fAbilityCooldown) {
				m_pDruidAbilityOne.AbilityPressed(m_pTimer->GetTime(), m_fAbilityCooldown);
			}
			break;
		}
	}

	if (input == eInput::KeyE) {
		switch (charSelected) {
		case eCharSelected::Rogue:
			if (currentTime - m_pRogueAbilityTwo.GetPressedTime() > m_fAbilityCooldown) {
				m_pRogueAbilityTwo.AbilityPressed(m_pTimer->GetTime(), m_fAbilityCooldown);
			}
			break;
		case eCharSelected::Warrior:
			if (currentTime - m_pWarriorAbilityTwo.GetPressedTime() > m_fAbilityCooldown) {
				m_pWarriorAbilityTwo.AbilityPressed(m_pTimer->GetTime(), m_fAbilityCooldown);
			}
			break;
		case eCharSelected::Druid:
			if (currentTime - m_pDruidAbilityTwo.GetPressedTime() > m_fAbilityCooldown) {
				m_pDruidAbilityTwo.AbilityPressed(m_pTimer->GetTime(), m_fAbilityCooldown);
			}
			break;
		}
	}

	if (input == eInput::KeyR) {
		switch (charSelected) {
		case eCharSelected::Rogue:
			if (currentTime - m_pRogueAbilityThree.GetPressedTime() > m_fAbilityCooldown) {
				m_pRogueAbilityThree.AbilityPressed(m_pTimer->GetTime(), m_fAbilityCooldown);
			}
			break;
		case eCharSelected::Warrior:
			if (currentTime - m_pWarriorAbilityThree.GetPressedTime() > m_fAbilityCooldown) {
				m_pWarriorAbilityThree.AbilityPressed(m_pTimer->GetTime(), m_fAbilityCooldown);
			}
			break;
		case eCharSelected::Druid:
			if (currentTime - m_pDruidAbilityThree.GetPressedTime() > m_fAbilityCooldown) {
				m_pDruidAbilityThree.AbilityPressed(m_pTimer->GetTime(), m_fAbilityCooldown);
			}
			break;
		}
	}
}

void CUIManager::MoveUI() {
	float m_fTime = m_pTimer->GetTime();
	float m_fElapsedTime = m_fTime - m_fCharSwitchTime;

	if (m_fElapsedTime > m_fCharSwitchCooldown) {
		m_pRogueFrame.SetToTargets();
		m_pWarriorFrame.SetToTargets();
		m_pDruidFrame.SetToTargets();

		m_pRogueHealthbar.SetToTargets();
		m_pWarriorHealthbar.SetToTargets();
		m_pDruidHealthbar.SetToTargets();

		m_pDruidManabar.SetToTargets();
	}
	else {
		float t = m_fElapsedTime / m_fCharSwitchCooldown;

		m_pRogueFrame.InterpToTargets(t);
		m_pWarriorFrame.InterpToTargets(t);
		m_pDruidFrame.InterpToTargets(t);

		m_pRogueHealthbar.InterpToTargets(t);
		m_pWarriorHealthbar.InterpToTargets(t);
		m_pDruidHealthbar.InterpToTargets(t);

		m_pDruidManabar.InterpToTargets(t);
	}

	switch (charSelected) {
	case eCharSelected::Rogue:
		m_fElapsedTime = m_fTime - m_pRogueAbilityOne.GetPressedTime();

		if (m_fElapsedTime > m_fAbilityCooldown)
			m_pRogueAbilityOne.SetToTargets();
		else
			m_pRogueAbilityOne.InterpToTargets(m_fElapsedTime / m_fAbilityCooldown);

		m_fElapsedTime = m_fTime - m_pRogueAbilityTwo.GetPressedTime();

		if (m_fElapsedTime > m_fAbilityCooldown)
			m_pRogueAbilityTwo.SetToTargets();
		else
			m_pRogueAbilityTwo.InterpToTargets(m_fElapsedTime / m_fAbilityCooldown);

		m_fElapsedTime = m_fTime - m_pRogueAbilityThree.GetPressedTime();

		if (m_fElapsedTime > m_fAbilityCooldown)
			m_pRogueAbilityThree.SetToTargets();
		else
			m_pRogueAbilityThree.InterpToTargets(m_fElapsedTime / m_fAbilityCooldown);

		break;
	case eCharSelected::Warrior:
		m_fElapsedTime = m_fTime - m_pWarriorAbilityOne.GetPressedTime();

		if (m_fElapsedTime > m_fAbilityCooldown)
			m_pWarriorAbilityOne.SetToTargets();
		else
			m_pWarriorAbilityOne.InterpToTargets(m_fElapsedTime / m_fAbilityCooldown);

		m_fElapsedTime = m_fTime - m_pWarriorAbilityTwo.GetPressedTime();

		if (m_fElapsedTime > m_fAbilityCooldown)
			m_pWarriorAbilityTwo.SetToTargets();
		else
			m_pWarriorAbilityTwo.InterpToTargets(m_fElapsedTime / m_fAbilityCooldown);

		m_fElapsedTime = m_fTime - m_pWarriorAbilityThree.GetPressedTime();

		if (m_fElapsedTime > m_fAbilityCooldown)
			m_pWarriorAbilityThree.SetToTargets();
		else
			m_pWarriorAbilityThree.InterpToTargets(m_fElapsedTime / m_fAbilityCooldown);

		break;
	case eCharSelected::Druid:
		m_fElapsedTime = m_fTime - m_pDruidAbilityOne.GetPressedTime();

		if (m_fElapsedTime > m_fAbilityCooldown)
			m_pDruidAbilityOne.SetToTargets();
		else
			m_pDruidAbilityOne.InterpToTargets(m_fElapsedTime / m_fAbilityCooldown);

		m_fElapsedTime = m_fTime - m_pDruidAbilityTwo.GetPressedTime();

		if (m_fElapsedTime > m_fAbilityCooldown)
			m_pDruidAbilityTwo.SetToTargets();
		else
			m_pDruidAbilityTwo.InterpToTargets(m_fElapsedTime / m_fAbilityCooldown);

		m_fElapsedTime = m_fTime - m_pDruidAbilityThree.GetPressedTime();

		if (m_fElapsedTime > m_fAbilityCooldown)
			m_pDruidAbilityThree.SetToTargets();
		else
			m_pDruidAbilityThree.InterpToTargets(m_fElapsedTime / m_fAbilityCooldown);

		break;
	}
}

void CUIManager::CalcAbilitiesTargets() {
	m_pRogueAbilityOne.CalcTargets(m_fAbilityOnePosX, m_fFrameOffset, m_fInactiveFrameHeight, m_fInactiveFrameHeight);
	m_pRogueAbilityTwo.CalcTargets(m_fAbilityTwoPosX, m_fFrameOffset, m_fInactiveFrameHeight, m_fInactiveFrameHeight);
	m_pRogueAbilityThree.CalcTargets(m_fAbilityThreePosX, m_fFrameOffset, m_fInactiveFrameHeight, m_fInactiveFrameHeight);

	m_pWarriorAbilityOne.CalcTargets(m_fAbilityOnePosX, m_fFrameOffset, m_fInactiveFrameHeight, m_fInactiveFrameHeight);
	m_pWarriorAbilityTwo.CalcTargets(m_fAbilityTwoPosX, m_fFrameOffset, m_fInactiveFrameHeight, m_fInactiveFrameHeight);
	m_pWarriorAbilityThree.CalcTargets(m_fAbilityThreePosX, m_fFrameOffset, m_fInactiveFrameHeight, m_fInactiveFrameHeight);

	m_pDruidAbilityOne.CalcTargets(m_fAbilityOnePosX, m_fFrameOffset, m_fInactiveFrameHeight, m_fInactiveFrameHeight);
	m_pDruidAbilityTwo.CalcTargets(m_fAbilityTwoPosX, m_fFrameOffset, m_fInactiveFrameHeight, m_fInactiveFrameHeight);
	m_pDruidAbilityThree.CalcTargets(m_fAbilityThreePosX, m_fFrameOffset, m_fInactiveFrameHeight, m_fInactiveFrameHeight);
}

void CUIManager::CalcFrameTargets() {
	switch (charSelected) {
		case eCharSelected::Rogue:
			m_pRogueFrame.CalcTargetScale(m_fActiveFrameHeight);
			m_pWarriorFrame.CalcTargetScale(m_fInactiveFrameHeight);
			m_pDruidFrame.CalcTargetScale(m_fInactiveFrameHeight);
			break;
		case eCharSelected::Warrior:
			m_pRogueFrame.CalcTargetScale(m_fInactiveFrameHeight);
			m_pWarriorFrame.CalcTargetScale(m_fActiveFrameHeight);
			m_pDruidFrame.CalcTargetScale(m_fInactiveFrameHeight);
			break;
		case eCharSelected::Druid:
			m_pRogueFrame.CalcTargetScale(m_fInactiveFrameHeight);
			m_pWarriorFrame.CalcTargetScale(m_fInactiveFrameHeight);
			m_pDruidFrame.CalcTargetScale(m_fActiveFrameHeight);
			break;
	}

	Vector3 pos = m_pCamera->GetPos();

	m_pRogueFrame.CalcTargetPos((float)m_nWinHeight);
	m_pWarriorFrame.CalcTargetPos(m_pRogueFrame.m_fTargetPosY - m_pRogueFrame.m_fTargetPosX - m_fFrameOffset);
	m_pDruidFrame.CalcTargetPos(m_pWarriorFrame.m_fTargetPosY - m_pWarriorFrame.m_fTargetPosX - m_fFrameOffset);
}

void CUIManager::CalcHealthbarsTargets() {
	switch (charSelected) {
		case eCharSelected::Rogue:
			m_pRogueHealthbar.CalcTargets(m_pRogueFrame.m_fTargetPosX, m_pRogueFrame.m_fTargetPosY, m_fActiveHealthbarWidth, m_fActiveHealthbarHeight);
			m_pWarriorHealthbar.CalcTargets(m_pWarriorFrame.m_fTargetPosX, m_pWarriorFrame.m_fTargetPosY, m_fInactiveHealthbarWidth, m_fInactiveHealthbarHeight);
			m_pDruidHealthbar.CalcTargets(m_pDruidFrame.m_fTargetPosX, m_pDruidFrame.m_fTargetPosY, m_fInactiveHealthbarWidth, m_fInactiveHealthbarHeight);
			
			m_pDruidManabar.CalcTargets(m_pDruidFrame.m_fTargetPosX, m_pDruidFrame.m_fTargetPosY, m_fInactiveHealthbarWidth, m_fInactiveHealthbarHeight);
			break;
		case eCharSelected::Warrior:
			m_pRogueHealthbar.CalcTargets(m_pRogueFrame.m_fTargetPosX, m_pRogueFrame.m_fTargetPosY, m_fInactiveHealthbarWidth, m_fInactiveHealthbarHeight);
			m_pWarriorHealthbar.CalcTargets(m_pWarriorFrame.m_fTargetPosX, m_pWarriorFrame.m_fTargetPosY, m_fActiveHealthbarWidth, m_fActiveHealthbarHeight);
			m_pDruidHealthbar.CalcTargets(m_pDruidFrame.m_fTargetPosX, m_pDruidFrame.m_fTargetPosY, m_fInactiveHealthbarWidth, m_fInactiveHealthbarHeight);
			
			m_pDruidManabar.CalcTargets(m_pDruidFrame.m_fTargetPosX, m_pDruidFrame.m_fTargetPosY, m_fInactiveHealthbarWidth, m_fInactiveHealthbarHeight);
			break;
		case eCharSelected::Druid:
			m_pRogueHealthbar.CalcTargets(m_pRogueFrame.m_fTargetPosX, m_pRogueFrame.m_fTargetPosY, m_fInactiveHealthbarWidth, m_fInactiveHealthbarHeight);
			m_pWarriorHealthbar.CalcTargets(m_pWarriorFrame.m_fTargetPosX, m_pWarriorFrame.m_fTargetPosY, m_fInactiveHealthbarWidth, m_fInactiveHealthbarHeight);
			m_pDruidHealthbar.CalcTargets(m_pDruidFrame.m_fTargetPosX, m_pDruidFrame.m_fTargetPosY, m_fActiveHealthbarWidth, m_fActiveHealthbarHeight);
			
			m_pDruidManabar.CalcTargets(m_pDruidFrame.m_fTargetPosX, m_pDruidFrame.m_fTargetPosY, m_fActiveHealthbarWidth, m_fActiveHealthbarHeight);
			break;
	}
}

void CUIManager::DrawUI() {
	MoveUI();

	m_pRenderer->Draw(&m_pRogueFrame.GetSprite());
	m_pRenderer->Draw(&m_pWarriorFrame.GetSprite());
	m_pRenderer->Draw(&m_pDruidFrame.GetSprite());

	m_pRenderer->Draw(&m_pRogueHealthbar.GetBackgroundSprite());
	m_pRenderer->Draw(&m_pRogueHealthbar.GetBarSprite());

	m_pRenderer->Draw(&m_pWarriorHealthbar.GetBackgroundSprite());
	m_pRenderer->Draw(&m_pWarriorHealthbar.GetBarSprite());

	m_pRenderer->Draw(&m_pDruidHealthbar.GetBackgroundSprite());
	m_pRenderer->Draw(&m_pDruidHealthbar.GetBarSprite());

	m_pRenderer->Draw(&m_pDruidManabar.GetBackgroundSprite());
	m_pRenderer->Draw(&m_pDruidManabar.GetBarSprite());

	switch (charSelected) {
	case eCharSelected::Rogue:
		m_pRenderer->Draw(&m_pRogueAbilityOne.GetBackgroundSprite());
		m_pRenderer->Draw(&m_pRogueAbilityOne.GetBarSprite());
		m_pRenderer->Draw(&m_pRogueAbilityTwo.GetBackgroundSprite());
		m_pRenderer->Draw(&m_pRogueAbilityTwo.GetBarSprite());
		m_pRenderer->Draw(&m_pRogueAbilityThree.GetBackgroundSprite());
		m_pRenderer->Draw(&m_pRogueAbilityThree.GetBarSprite());
		break;
	case eCharSelected::Warrior:
		m_pRenderer->Draw(&m_pWarriorAbilityOne.GetBackgroundSprite());
		m_pRenderer->Draw(&m_pWarriorAbilityOne.GetBarSprite());
		m_pRenderer->Draw(&m_pWarriorAbilityTwo.GetBackgroundSprite());
		m_pRenderer->Draw(&m_pWarriorAbilityTwo.GetBarSprite());
		m_pRenderer->Draw(&m_pWarriorAbilityThree.GetBackgroundSprite());
		m_pRenderer->Draw(&m_pWarriorAbilityThree.GetBarSprite());
		break;
	case eCharSelected::Druid:
		m_pRenderer->Draw(&m_pDruidAbilityOne.GetBackgroundSprite());
		m_pRenderer->Draw(&m_pDruidAbilityOne.GetBarSprite());
		m_pRenderer->Draw(&m_pDruidAbilityTwo.GetBackgroundSprite());
		m_pRenderer->Draw(&m_pDruidAbilityTwo.GetBarSprite());
		m_pRenderer->Draw(&m_pDruidAbilityThree.GetBackgroundSprite());
		m_pRenderer->Draw(&m_pDruidAbilityThree.GetBarSprite());
		break;
	}
}