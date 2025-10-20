#pragma once
#include "SpriteRenderer.h"
#include "UIWidgetResourceBar.h"

struct UIWidgetAbility : public UIWidgetResourceBar {
public:
	float m_fPressedTime = -1.0f;

	void CalcTargets(float m_fFrameTargetPosX, float m_fFrameTargetPosY, float m_fTargetWidth, float m_fTargetHeight);
};