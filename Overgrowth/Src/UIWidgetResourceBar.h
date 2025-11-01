#pragma once
#include "UIWidget.h"

class UIWidgetResourceBar : public UIWidget {
private:
	LSpriteDesc3D m_pBarSprite;

	float m_fBarSpriteSizeX = 0.0f;
	float m_fBarSpriteSizeY = 0.0f;
public:
	float m_fBarTargetScaleX = 0.0f;
	float m_fBarTargetScaleY = 0.0f;

	float m_fBarTargetPosX = 0.0f;
	float m_fBarTargetPosY = 0.0f;
	float m_fBarTargetPosZ = 0.0f;

	void SetBarTargets(float scaleX, float scaleY, Vector3 pos);
	void SetBarToTargets();
	void InterpBarToTargets(float t);

	void SetBarSprite(eSprite sprite, float w, float h);

	float GetBarSizeX() { return m_fBarSpriteSizeX; }
	float GetBarSizeY() { return m_fBarSpriteSizeY; }
	LSpriteDesc3D GetBarSprite() { return m_pBarSprite; }
};