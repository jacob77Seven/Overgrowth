#pragma once
#include "Common.h"
#include "UIWidget.h"
#include "UIWidgetResourceBar.h"
#include "UIWidgetAbility.h"

class CUIManager :
    public LComponent,
	public LSettings,
    public OCommon {
private:
    UIWidget m_pRogueFrame;
    UIWidget m_pWarriorFrame;
    UIWidget m_pDruidFrame;

    UIWidgetResourceBar m_pRogueHealthBar;
    UIWidgetResourceBar m_pWarriorHealthBar;
    UIWidgetResourceBar m_pDruidHealthBar;
    UIWidgetResourceBar m_pDruidManaBar;
    
    eCharSelected charSelected = eCharSelected::Rogue;

    float m_fLargeIconHeight = m_nWinHeight * 0.026f;
    float m_fSmallIconHeight = m_fLargeIconHeight * 0.75f;
    float m_fIconToIconOffset = -m_fLargeIconHeight * 0.1f;

    float m_fLargeBarHeight = m_fLargeIconHeight * 0.15f;
    float m_fLargeBarWidth = m_fLargeIconHeight * 2.0f;
    float m_fSmallBarHeight = m_fSmallIconHeight * 0.15f;
    float m_fSmallBarWidth = m_fSmallIconHeight * 2.0f;

    float m_fLargeIconXOffset = -185.5f;
    float m_fLargeIconYOffset = 98.5f;
    float m_fSmallIconXOffset = -189.0f;
    float m_fSmallIconYOffset = 102.0f;

    float m_fPosZ = 0.0f;
    float m_fZOffset = 500.0f;

    float m_fCharSwitchSpeed = 10.0f;

    void CalcFramesTargets();
    void CalcResourceBarsTargets();
    void CalcAbilitiesTargets();
public:
    void InitializeUI();
    void MoveUI(float t);
    void DrawUI();
};