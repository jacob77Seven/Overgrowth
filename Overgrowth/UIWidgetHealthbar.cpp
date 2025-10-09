#include "UIWidgetHealthbar.h"

void UIWidgetHealthbar::SetBackgroundSprite(UINT index, const LSpriteRenderer* m_pRenderer) {
	m_pBackgroundSprite.m_nSpriteIndex = index;
	m_pRenderer->GetSize(index, m_fBackgroundSpriteSizeX, m_fBackgroundSpriteSizeY);
}

void UIWidgetHealthbar::SetHealthbarSprite(UINT index, const LSpriteRenderer* m_pRenderer) {
	m_pHealthbarSprite.m_nSpriteIndex = index;
	m_pRenderer->GetSize(index, m_fHealthbarSpriteSizeX, m_fHealthbarSpriteSizeY);
}

void UIWidgetHealthbar::SetToTargets() {
	m_pBackgroundSprite.m_vPos.x = m_fBackgroundTargetPosX;
	m_pBackgroundSprite.m_vPos.y = m_fBackgroundTargetPosY;
	m_pBackgroundSprite.m_fXScale = m_fBackgroundTargetScaleX;
	m_pBackgroundSprite.m_fYScale = m_fBackgroundTargetScaleY;

	m_pHealthbarSprite.m_vPos.x = m_fHealthbarTargetPosX;
	m_pHealthbarSprite.m_vPos.y = m_fHealthbarTargetPosY;
	m_pHealthbarSprite.m_fXScale = m_fHealthbarTargetScaleX;
	m_pHealthbarSprite.m_fYScale = m_fHealthbarTargetScaleY;
}

void UIWidgetHealthbar::InterpToTargets(float t) {
	m_pBackgroundSprite.m_vPos.x = m_pBackgroundSprite.m_vPos.x + (m_fBackgroundTargetPosX - m_pBackgroundSprite.m_vPos.x) * t;
	m_pBackgroundSprite.m_vPos.y = m_pBackgroundSprite.m_vPos.y + (m_fBackgroundTargetPosY - m_pBackgroundSprite.m_vPos.y) * t;
	m_pBackgroundSprite.m_fXScale = m_pBackgroundSprite.m_fXScale + (m_fBackgroundTargetScaleX - m_pBackgroundSprite.m_fXScale) * t;
	m_pBackgroundSprite.m_fYScale = m_pBackgroundSprite.m_fYScale + (m_fBackgroundTargetScaleY - m_pBackgroundSprite.m_fYScale) * t;

	m_pHealthbarSprite.m_vPos.x = m_pHealthbarSprite.m_vPos.x + (m_fHealthbarTargetPosX - m_pHealthbarSprite.m_vPos.x) * t;
	m_pHealthbarSprite.m_vPos.y = m_pHealthbarSprite.m_vPos.y + (m_fHealthbarTargetPosY - m_pHealthbarSprite.m_vPos.y) * t;
	m_pHealthbarSprite.m_fXScale = m_pHealthbarSprite.m_fXScale + (m_fHealthbarTargetScaleX - m_pHealthbarSprite.m_fXScale) * t;
	m_pHealthbarSprite.m_fYScale = m_pHealthbarSprite.m_fYScale + (m_fHealthbarTargetScaleY - m_pHealthbarSprite.m_fYScale) * t;
}

void UIWidgetHealthbar::CalcTargets(float m_fFrameTargetPosX, float m_fFrameTargetPosY, float m_fTargetWidth, float m_fTargetHeight) {
	float m_fBottomLeftCornerX = m_fFrameTargetPosX * 2;
	float m_fBottomLeftCornerY = m_fFrameTargetPosY - m_fFrameTargetPosX;

	m_fBackgroundTargetScaleX = 1 / (m_fBackgroundSpriteSizeX / m_fTargetWidth);
	m_fBackgroundTargetScaleY = 1 / (m_fBackgroundSpriteSizeY / m_fTargetHeight);

	m_fHealthbarTargetScaleX = (1 / (m_fHealthbarSpriteSizeX / m_fTargetWidth)) * 0.5f;
	m_fHealthbarTargetScaleY = 1 / (m_fHealthbarSpriteSizeY / m_fTargetHeight);

	m_fBackgroundTargetPosX = m_fBottomLeftCornerX + (m_fBackgroundSpriteSizeX * m_fBackgroundTargetScaleX / 2);
	m_fBackgroundTargetPosY = m_fBottomLeftCornerY + (m_fBackgroundSpriteSizeY * m_fBackgroundTargetScaleY / 2);

	m_fHealthbarTargetPosX = m_fBottomLeftCornerX + (m_fHealthbarSpriteSizeX * m_fHealthbarTargetScaleX / 2);
	m_fHealthbarTargetPosY = m_fBottomLeftCornerY + (m_fHealthbarSpriteSizeY * m_fHealthbarTargetScaleY / 2);
}