#pragma once
#include "Common.h"
#include "InputInterface.h"
#include "UIWidgetCharFrame.h"
#include "UIWidgetHealthBar.h"
#include "UIWidgetManaBar.h"

class CUIManager :
    public LComponent,
	public LSettings,
    public CCommon,
    public IInput {
private:
    UIWidgetCharFrame m_pRogueFrame;
    UIWidgetCharFrame m_pWarriorFrame;
    UIWidgetCharFrame m_pDruidFrame;

    UIWidgetHealthBar m_pRogueHealthbar;
    UIWidgetHealthBar m_pWarriorHealthbar;
    UIWidgetHealthBar m_pDruidHealthbar;
    UIWidgetManaBar m_pDruidManabar;

    float m_fActiveFrameHeight = m_nWinHeight * 0.15f;
    float m_fInactiveFrameHeight = m_nWinHeight * 0.1f;
    float m_fFrameOffset = m_nWinHeight * 0.01f;

    float m_fActiveHealthbarHeight = m_fActiveFrameHeight * 0.15f;
    float m_fActiveHealthbarWidth = m_fActiveHealthbarHeight * 10.0f;
    float m_fInactiveHealthbarHeight = m_fInactiveFrameHeight * 0.15f;
    float m_fInactiveHealthbarWidth = m_fInactiveHealthbarHeight * 10.0f;

    float m_fCharSwitchCooldown = 0.5f;
    float m_fCharSwitchTime = -1.0f;

    void MoveUI();
    void CalcHealthbarsTargets(const eInput& input);
    void SetActiveCharFrame(const eInput& input);
public:
    void InitializeUI();
    void DrawUI();
    void Input(const eInput& input) override;

    float GetCharSwitchCooldown() { return m_fCharSwitchCooldown; };
    float GetCharSwitchTime() { return m_fCharSwitchTime; };
};