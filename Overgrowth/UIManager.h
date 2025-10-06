#pragma once
#include "Common.h"

class CUIManager :
	public LSettings,
    public CCommon {
private:
    LSpriteDesc2D m_pRogueCharFrame;
    LSpriteDesc2D m_pWarriorCharFrame;
    LSpriteDesc2D m_pDruidCharFrame;

    Vector2 m_vRogueCharFrameSize;
    Vector2 m_vWarriorCharFrameSize;
    Vector2 m_vDruidCharFrameSize;

    float m_fActiveHeight = m_nWinHeight * .15f;
    float m_fInactiveHeight = m_nWinHeight * .1f;
    float offset = m_nWinHeight * .01f;

    void InactiveCharFrame(UINT c);
    void PositionCharFrames();
public:
    void InitializeUI();
    void DrawUI();
    void ActiveCharFrame(UINT c);
};