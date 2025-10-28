#pragma once
#include "SpriteRenderer.h"
#include "UIWidgetResourceBar.h"

struct UIWidgetAbility : public UIWidgetResourceBar {
private:
	float m_fPressedTime = -5.0f;

	float m_fInitialPosY = 0.0f;
	float m_fInitialScaleY = 0.0f;

public:

	void AbilityPressed(float time, float m_fCooldown);

	void CalcTargets(float m_fFrameTargetPosX, float m_fFrameTargetPosY, float m_fTargetWidth, float m_fTargetHeight);

	void SetBarSprite(UINT index, const ORenderer* m_pRenderer) override;
	void InterpToTargets(float t) override;

	float GetPressedTime() { return m_fPressedTime; }
};