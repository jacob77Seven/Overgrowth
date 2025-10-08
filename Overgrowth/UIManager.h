#pragma once
#include "Common.h"

class CUIManager :
    public LComponent,
	public LSettings,
    public CCommon {
private:
    LSpriteDesc2D m_pRogueFrame;
    LSpriteDesc2D m_pWarriorFrame;
    LSpriteDesc2D m_pDruidFrame;

    Vector2 m_vRogueSpriteSize;
    Vector2 m_vWarriorSpriteSize;
    Vector2 m_vDruidSpriteSize;

    Vector2 m_vTargetRogueFramePos;
    Vector2 m_vTargetWarriorFramePos;
    Vector2 m_vTargetDruidFramePos;

    Vector2 m_vTargetRogueFrameScale;
    Vector2 m_vTargetWarriorFrameScale;
    Vector2 m_vTargetDruidFrameScale;

    float m_fActiveHeight = m_nWinHeight * 0.15f;
    float m_fInactiveHeight = m_nWinHeight * 0.1f;
    float m_fOffset = m_nWinHeight * 0.01f;
    float m_fCharSwitchCooldown = 0.5f;
    float m_fCharSwitchTime;

    void InterpPos(LSpriteDesc2D* m_pCharFrame, Vector2* m_vTargetPos);

    void InactiveCharFrame(UINT c);
    void CalcTargetPos();
    void MoveCharFrames();
public:
    void InitializeUI();
    void DrawUI();
    void ActiveCharFrame(UINT c);

    float GetCharSwitchCooldown() { return m_fCharSwitchCooldown; };
    float GetCharSwitchTime() { return m_fCharSwitchTime; };
};