#pragma once
#include "Common.h"
#include "InputInterface.h"
#include "UIWidget.h"
#include "UIWidgetResourceBar.h"
#include "UIWidgetAbility.h"

class CUIManager :
    public LComponent,
	public LSettings,
    public OCommon {
private:
    UIWidget m_pRogueFrame;

    Vector3 m_vCameraPos = Vector3(0.0f, 0.0f, 0.0f);

    float m_fLargeIconHeight = m_nWinHeight * 0.026f;
    float m_fSmallIconHeight = m_fLargeIconHeight * 0.9f;

    float m_fLargeIconXOffset = -186.1f;
    float m_fLargeIconYOffset = 99.0f;

    float m_fZOffset = 500.0f;

    void CalcHealthbarsTargets();
    void CalcAbilitiesTargets();
    void CalcFrameTargets();
    void MoveUI();
public:
    void InitializeUI();
    void DrawUI();
};