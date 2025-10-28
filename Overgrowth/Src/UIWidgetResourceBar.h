#pragma once
#include "SpriteRenderer.h"
#include "Renderer.h"

struct UIWidgetResourceBar {
protected:
	LSpriteDesc3D m_pBackgroundSprite;
	LSpriteDesc3D m_pBarSprite;

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
	virtual void InterpToTargets(float t);

	virtual void CalcTargets(float m_fFrameTargetPosX, float m_fFrameTargetPosY, float m_fTargetWidth, float m_fTargetHeight) = 0;

	void SetBackgroundSprite(UINT index, const ORenderer* m_pRenderer);
	virtual void SetBarSprite(UINT index, const ORenderer* m_pRenderer);

	LSpriteDesc3D& GetBackgroundSprite() { return m_pBackgroundSprite; };
	LSpriteDesc3D& GetBarSprite() { return m_pBarSprite; };
};