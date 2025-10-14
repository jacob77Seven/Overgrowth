#pragma once
#include "SpriteRenderer.h"

struct UIWidgetHealthbar {
private:
	LSpriteDesc2D m_pBackgroundSprite;
	LSpriteDesc2D m_pHealthbarSprite;

	float m_fBackgroundSpriteSizeX = 0.0f;
	float m_fBackgroundSpriteSizeY = 0.0f;

	float m_fHealthbarSpriteSizeX = 0.0f;
	float m_fHealthbarSpriteSizeY = 0.0f;
public:
	float m_fBackgroundTargetPosX = 0.0f;
	float m_fBackgroundTargetPosY = 0.0f;
	float m_fBackgroundTargetScaleX = 1.0f;
	float m_fBackgroundTargetScaleY = 1.0f;

	float m_fHealthbarTargetPosX = 0.0f;
	float m_fHealthbarTargetPosY = 0.0f;
	float m_fHealthbarTargetScaleX = 1.0f;
	float m_fHealthbarTargetScaleY = 1.0f;

	void SetToTargets();
	void InterpToTargets(float t);

	void CalcTargets(float m_fFrameTargetPosX, float m_fFrameTargetPosY, float m_fTargetWidth, float m_fTargetHeight);

	void SetBackgroundSprite(UINT index, const LSpriteRenderer* m_pRenderer);
	void SetHealthbarSprite(UINT index, const LSpriteRenderer* m_pRenderer);

	LSpriteDesc2D& GetBackgroundSprite() { return m_pBackgroundSprite; };
	LSpriteDesc2D& GetHealthbarSprite() { return m_pHealthbarSprite; };
};