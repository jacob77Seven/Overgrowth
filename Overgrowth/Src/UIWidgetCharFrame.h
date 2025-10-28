#pragma once
#include "SpriteRenderer.h"
#include "Renderer.h"

struct UIWidgetCharFrame {
private:
	LSpriteDesc3D m_pSprite;
	
	float m_fSpriteSizeX = 0.0f;
	float m_fSpriteSizeY = 0.0f;
public:
	float m_fTargetPosX = 0.0f;
	float m_fTargetPosY = 0.0f;
	float m_fTargetScaleX = 1.0f;
	float m_fTargetScaleY = 1.0f;

	void SetToTargets();
	void InterpToTargets(float t);

	void CalcTargetPos(float m_fMaxHeight);
	void CalcTargetScale(float m_fTargetHeight);

	void SetSprite(UINT index, const ORenderer* m_pRenderer);

	LSpriteDesc3D& GetSprite() { return m_pSprite; };
};