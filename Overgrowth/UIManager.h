#pragma once
#include "Common.h"
#include "UIWidgetCharFrame.h"

class CUIManager :
    public LComponent,
	public LSettings,
    public CCommon {
private:
    UIWidgetCharFrame m_pRogueFrame;
    UIWidgetCharFrame m_pWarrior;
    UIWidgetCharFrame m_pDruid;

    float m_fActiveHeight = m_nWinHeight * 0.15f;
    float m_fInactiveHeight = m_nWinHeight * 0.1f;
    float m_fOffset = m_nWinHeight * 0.01f;
    float m_fCharSwitchCooldown = 0.5f;
    float m_fCharSwitchTime;

    void CalcFramesTargetPos();
    void MoveFrames();
public:
    void InitializeUI();
    void DrawUI();
    void SetActiveCharFrame(UINT c);

    float GetCharSwitchCooldown() { return m_fCharSwitchCooldown; };
    float GetCharSwitchTime() { return m_fCharSwitchTime; };
};