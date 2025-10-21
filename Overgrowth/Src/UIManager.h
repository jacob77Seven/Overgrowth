#pragma once
#include "Common.h"
#include "InputInterface.h"
#include "UIWidgetCharFrame.h"
#include "UIWidgetHealthBar.h"
#include "UIWidgetManaBar.h"
#include "UIWidgetAbility.h"



class CUIManager :
    public LComponent,
	public LSettings,
    public CCommon,
    public IInput {
private:
    enum class eCharSelected : UINT {
        Rogue, Warrior, Druid
    };

    UIWidgetCharFrame m_pRogueFrame;
    UIWidgetCharFrame m_pWarriorFrame;
    UIWidgetCharFrame m_pDruidFrame;

    UIWidgetHealthBar m_pRogueHealthbar;
    UIWidgetHealthBar m_pWarriorHealthbar;
    UIWidgetHealthBar m_pDruidHealthbar;
    UIWidgetManaBar m_pDruidManabar;

    UIWidgetAbility m_pRogueAbilityOne;
    UIWidgetAbility m_pRogueAbilityTwo;
    UIWidgetAbility m_pRogueAbilityThree;

    UIWidgetAbility m_pWarriorAbilityOne;
    UIWidgetAbility m_pWarriorAbilityTwo;
    UIWidgetAbility m_pWarriorAbilityThree;

    UIWidgetAbility m_pDruidAbilityOne;
    UIWidgetAbility m_pDruidAbilityTwo;
    UIWidgetAbility m_pDruidAbilityThree;

    eCharSelected charSelected = eCharSelected::Rogue;

    float m_fActiveFrameHeight = m_nWinHeight * 0.15f;
    float m_fInactiveFrameHeight = m_nWinHeight * 0.1f;
    float m_fFrameOffset = m_nWinHeight * 0.01f;

    float m_fActiveHealthbarHeight = m_fActiveFrameHeight * 0.15f;
    float m_fActiveHealthbarWidth = m_fActiveHealthbarHeight * 10.0f;
    float m_fInactiveHealthbarHeight = m_fInactiveFrameHeight * 0.15f;
    float m_fInactiveHealthbarWidth = m_fInactiveHealthbarHeight * 10.0f;

    float m_fAbilityOffset = m_nWinWidth * 0.1f;
    float m_fAbilityTwoPosX = m_nWinWidth / 2.0f;
    float m_fAbilityOnePosX = m_fAbilityTwoPosX - m_fAbilityOffset;
    float m_fAbilityThreePosX = m_fAbilityTwoPosX + m_fAbilityOffset;

    float m_fCharSwitchCooldown = 0.5f;
    float m_fCharSwitchTime = -1.0f;

    float m_fAbilityCooldown = 2.0f;

    void MoveUI();
    void CalcHealthbarsTargets();
    void CalcAbilitiesTargets();
    void CalcFrameTargets();
public:
    void InitializeUI();
    void DrawUI();
    void Input(const eInput& input) override;

    float GetCharSwitchCooldown() { return m_fCharSwitchCooldown; };
    float GetCharSwitchTime() { return m_fCharSwitchTime; };
};