#pragma once
#include "SpriteRenderer.h"

struct UIWidgetManabar {
private:
	LSpriteDesc2D m_pBackgroundSprite;
	LSpriteDesc2D m_pManabarSprite;

	float m_fBackgroundSpriteSizeX = 0.0f;
	float m_fBackgroundSpriteSizeY = 0.0f;

	float m_fManabarSpriteSizeX = 0.0f;
	float m_fManabarSpriteSizeY = 0.0f;
public:
	float m_fBackgroundTargetPosX = 0.0f;
	float m_fBackgroundTargetPosY = 0.0f;
	float m_fBackgroundTargetScaleX = 1.0f;
	float m_fBackgroundTargetScaleY = 1.0f;

	float m_fManabarTargetPosX = 0.0f;
	float m_fManabarTargetPosY = 0.0f;
	float m_fManabarTargetScaleX = 1.0f;
	float m_fManabarTargetScaleY = 1.0f;

	void SetToTargets();
	void InterpToTargets(float t);

	void CalcTargets(float m_fFrameTargetPosX, float m_fFrameTargetPosY, float m_fTargetWidth, float m_fTargetHeight);

	void SetBackgroundSprite(UINT index, const LSpriteRenderer* m_pRenderer);
	void SetManabarSprite(UINT index, const LSpriteRenderer* m_pRenderer);

	LSpriteDesc2D& GetBackgroundSprite() { return m_pBackgroundSprite; };
	LSpriteDesc2D& GetManabarSprite() { return m_pManabarSprite; };
};