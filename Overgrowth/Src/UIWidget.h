#pragma once
#include "SpriteRenderer.h"
#include "Renderer.h"
#include "../GameDefines.h"

class UIWidget {
private:
	LSpriteDesc3D m_pSprite;

	float m_fSpriteSizeX = 0.0f;
	float m_fSpriteSizeY = 0.0f;
public:
	float m_fTargetScaleX = 0.0f;
	float m_fTargetScaleY = 0.0f;

	float m_fTargetPosX = 0.0f;
	float m_fTargetPosY = 0.0f;
	float m_fTargetPosZ = 0.0f;

	void SetToTargets();
	void SetTargets(float scaleX, float scaleY, Vector3 pos);

	void SetSprite(eSprite sprite, float w, float h);

	float GetSizeX() { return m_fSpriteSizeX; }
	float GetSizeY() { return m_fSpriteSizeY; }
	LSpriteDesc3D GetSprite() { return m_pSprite; }
};