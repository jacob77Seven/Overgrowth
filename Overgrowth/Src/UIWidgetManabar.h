#pragma once
#include "SpriteRenderer.h"
#include "UIWidgetResourceBar.h"

struct UIWidgetManaBar : public UIWidgetResourceBar {
	void CalcTargets(float m_fFrameTargetPosX, float m_fFrameTargetPosY, float m_fTargetWidth, float m_fTargetHeight);
};