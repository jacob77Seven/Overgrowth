#pragma once
#include "SpriteRenderer.h"

struct UIWidgetCharFrame {
private:
	LSpriteDesc2D m_pSprite;
	
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

	void SetSprite(UINT index, const LSpriteRenderer* m_pRenderer);
	void SetSpritePosX(float pos) { m_pSprite.m_vPos.x = pos; };
	void SetSpritePosY(float pos) { m_pSprite.m_vPos.y = pos; };
	void SetSpriteScaleX(float scale) { m_pSprite.m_fXScale = scale; };
	void SetSpriteScaleY(float scale) { m_pSprite.m_fYScale = scale; };

	LSpriteDesc2D& GetSprite() { return m_pSprite; };
	float GetSpriteSizeX() { return m_fSpriteSizeX; };
	float GetSpriteSizeY() { return m_fSpriteSizeY; };
	float GetSpriteScaleX() { return m_pSprite.m_fXScale; };
	float GetSpriteScaleY() { return m_pSprite.m_fYScale; };
};