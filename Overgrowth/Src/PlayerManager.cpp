#include "../GameDefines.h"

#include "PlayerManager.h"

void PlayerManager::Input(const eInput& input) {
	float time = m_pTimer->GetTime();

	if(time - m_fCharSwitchTime > m_fCharSwitchCooldown) {
		m_fCharSwitchTime = time;

		switch (input) {
		case eInput::KeyOne:
			charSelected = eCharSelected::Rogue;
			break;
		case eInput::KeyTwo:
			charSelected = eCharSelected::Warrior;
			break;
		case eInput::KeyThree:
			charSelected = eCharSelected::Druid;
			break;
		}
	}
}

bool PlayerManager::IsSwitchingChar() {
	float time = m_pTimer->GetTime();
	return time - m_fCharSwitchTime <= m_fCharSwitchCooldown;
}