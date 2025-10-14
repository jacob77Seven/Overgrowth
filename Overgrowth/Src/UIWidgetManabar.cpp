#include "UIWidgetManabar.h"

void UIWidgetManabar::SetBackgroundSprite(UINT index, const LSpriteRenderer* m_pRenderer) {
	m_pBackgroundSprite.m_nSpriteIndex = index;
	m_pRenderer->GetSize(index, m_fBackgroundSpriteSizeX, m_fBackgroundSpriteSizeY);
}

void UIWidgetManabar::SetManabarSprite(UINT index, const LSpriteRenderer* m_pRenderer) {
	m_pManabarSprite.m_nSpriteIndex = index;
	m_pRenderer->GetSize(index, m_fManabarSpriteSizeX, m_fManabarSpriteSizeY);
}

void UIWidgetManabar::SetToTargets() {
	m_pBackgroundSprite.m_vPos.x = m_fBackgroundTargetPosX;
	m_pBackgroundSprite.m_vPos.y = m_fBackgroundTargetPosY;
	m_pBackgroundSprite.m_fXScale = m_fBackgroundTargetScaleX;
	m_pBackgroundSprite.m_fYScale = m_fBackgroundTargetScaleY;

	m_pManabarSprite.m_vPos.x = m_fManabarTargetPosX;
	m_pManabarSprite.m_vPos.y = m_fManabarTargetPosY;
	m_pManabarSprite.m_fXScale = m_fManabarTargetScaleX;
	m_pManabarSprite.m_fYScale = m_fManabarTargetScaleY;
}

void UIWidgetManabar::InterpToTargets(float t) {
	m_pBackgroundSprite.m_vPos.x = m_pBackgroundSprite.m_vPos.x + (m_fBackgroundTargetPosX - m_pBackgroundSprite.m_vPos.x) * t;
	m_pBackgroundSprite.m_vPos.y = m_pBackgroundSprite.m_vPos.y + (m_fBackgroundTargetPosY - m_pBackgroundSprite.m_vPos.y) * t;
	m_pBackgroundSprite.m_fXScale = m_pBackgroundSprite.m_fXScale + (m_fBackgroundTargetScaleX - m_pBackgroundSprite.m_fXScale) * t;
	m_pBackgroundSprite.m_fYScale = m_pBackgroundSprite.m_fYScale + (m_fBackgroundTargetScaleY - m_pBackgroundSprite.m_fYScale) * t;

	m_pManabarSprite.m_vPos.x = m_pManabarSprite.m_vPos.x + (m_fManabarTargetPosX - m_pManabarSprite.m_vPos.x) * t;
	m_pManabarSprite.m_vPos.y = m_pManabarSprite.m_vPos.y + (m_fManabarTargetPosY - m_pManabarSprite.m_vPos.y) * t;
	m_pManabarSprite.m_fXScale = m_pManabarSprite.m_fXScale + (m_fManabarTargetScaleX - m_pManabarSprite.m_fXScale) * t;
	m_pManabarSprite.m_fYScale = m_pManabarSprite.m_fYScale + (m_fManabarTargetScaleY - m_pManabarSprite.m_fYScale) * t;
}

void UIWidgetManabar::CalcTargets(float m_fFrameTargetPosX, float m_fFrameTargetPosY, float m_fTargetWidth, float m_fTargetHeight) {
	m_fBackgroundTargetScaleX = 1 / (m_fBackgroundSpriteSizeX / m_fTargetWidth);
	m_fBackgroundTargetScaleY = 1 / (m_fBackgroundSpriteSizeY / m_fTargetHeight);

	m_fManabarTargetScaleX = 1 / (m_fManabarSpriteSizeX / m_fTargetWidth);
	m_fManabarTargetScaleY = 1 / (m_fManabarSpriteSizeY / m_fTargetHeight);

	float m_fBottomLeftCornerX = m_fFrameTargetPosX * 2;
	float m_fBottomLeftCornerY = m_fFrameTargetPosY - m_fFrameTargetPosX + (m_fBackgroundSpriteSizeY * m_fBackgroundTargetScaleX * 1.2);

	m_fBackgroundTargetPosX = m_fBottomLeftCornerX + (m_fBackgroundSpriteSizeX * m_fBackgroundTargetScaleX / 2);
	m_fBackgroundTargetPosY = m_fBottomLeftCornerY + (m_fBackgroundSpriteSizeY * m_fBackgroundTargetScaleY / 2);

	m_fManabarTargetPosX = m_fBottomLeftCornerX + (m_fManabarSpriteSizeX * m_fManabarTargetScaleX / 2);
	m_fManabarTargetPosY = m_fBottomLeftCornerY + (m_fManabarSpriteSizeY * m_fManabarTargetScaleY / 2);
}