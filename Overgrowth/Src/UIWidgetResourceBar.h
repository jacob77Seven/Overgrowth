#pragma once
#include "SpriteRenderer.h"

struct UIWidgetResourceBar {
protected:
	LSpriteDesc2D m_pBackgroundSprite;
	LSpriteDesc2D m_pBarSprite;

	float m_fBackgroundSpriteSizeX = 0.0f;
	float m_fBackgroundSpriteSizeY = 0.0f;

	float m_fBarSpriteSizeX = 0.0f;
	float m_fBarSpriteSizeY = 0.0f;
public:
	float m_fBackgroundTargetPosX = 0.0f;
	float m_fBackgroundTargetPosY = 0.0f;
	float m_fBackgroundTargetScaleX = 1.0f;
	float m_fBackgroundTargetScaleY = 1.0f;

	float m_fBarTargetPosX = 0.0f;
	float m_fBarTargetPosY = 0.0f;
	float m_fBarTargetScaleX = 1.0f;
	float m_fBarTargetScaleY = 1.0f;

	void SetToTargets();
	void InterpToTargets(float t);

	virtual void CalcTargets(float m_fFrameTargetPosX, float m_fFrameTargetPosY, float m_fTargetWidth, float m_fTargetHeight) = 0;

	void SetBackgroundSprite(UINT index, const LSpriteRenderer* m_pRenderer);
	void SetBarSprite(UINT index, const LSpriteRenderer* m_pRenderer);

	LSpriteDesc2D& GetBackgroundSprite() { return m_pBackgroundSprite; };
	LSpriteDesc2D& GetBarSprite() { return m_pBarSprite; };
};