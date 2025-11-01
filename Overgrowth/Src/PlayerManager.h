#pragma once
#include "BaseCharacter.h"
#include "InputInterface.h"
#include "Common.h"
#include "../GameDefines.h"

class PlayerManager: 
    public LComponent,
    public IInput, 
    public OCommon {
protected:
    float m_fMaxHealth = 100.0f;
    float m_fHealth = 80.0f;

    float m_fMaxMana = 100.0f;
    float m_fMana = 80.0f;
    
    float m_fCharSwitchCooldown = 0.5f;
    float m_fCharSwitchTime = -1.0f;

    float m_fRogueAbilityOneTimeCooldown = 2.0f;
    float m_fRogueAbilityOneTimePressed = -1.0f;
    float m_fRogueAbilityTwoTimeCooldown = 2.0f;
    float m_fRogueAbilityTwoTimePressed = -1.0f;
    float m_fRogueAbilityThreeTimeCooldown = 2.0f;
    float m_fRogueAbilityThreeTimePressed = -1.0f;

    float m_fWarriorAbilityOneTimeCooldown = 2.0f;
    float m_fWarriorAbilityOneTimePressed = -1.0f;
    float m_fWarriorAbilityTwoTimeCooldown = 2.0f;
    float m_fWarriorAbilityTwoTimePressed = -1.0f;
    float m_fWarriorAbilityThreeTimeCooldown = 2.0f;
    float m_fWarriorAbilityThreeTimePressed = -1.0f;

    float m_fDruidAbilityOneTimeCooldown = 2.0f;
    float m_fDruidAbilityOneTimePressed = -1.0f;
    float m_fDruidAbilityTwoTimeCooldown = 2.0f;
    float m_fDruidAbilityTwoTimePressed = -1.0f;
    float m_fDruidAbilityThreeTimeCooldown = 2.0f;
    float m_fDruidAbilityThreeTimePressed = -1.0f;

    eCharSelected charSelected = eCharSelected::Rogue;

public:
    float GetHealth() { return m_fHealth / m_fMaxHealth; }
    float GetMana() { return m_fMana / m_fMaxMana; }
    eCharSelected GetCharSelected() { return charSelected; }

    bool IsSwitchingChar();

    void Input(const eInput& input) override;
};