#include "UIWidgetResourceBar.h"

void UIWidgetResourceBar::SetBackgroundSprite(UINT index, const ORenderer* m_pRenderer) {
	m_pBackgroundSprite.m_nSpriteIndex = index;
	m_pBackgroundSprite.m_vPos = Vector3(0.0f, 0.0f, 0.0f);
	m_pRenderer->GetSize(index, m_fBackgroundSpriteSizeX, m_fBackgroundSpriteSizeY);
}

void UIWidgetResourceBar::SetBarSprite(UINT index, const ORenderer* m_pRenderer) {
	m_pBarSprite.m_nSpriteIndex = index;
	m_pBarSprite.m_vPos = Vector3(0.0f, 0.0f, 0.0f);
	m_pRenderer->GetSize(index, m_fBarSpriteSizeX, m_fBarSpriteSizeY);
}

void UIWidgetResourceBar::SetToTargets() {
	m_pBackgroundSprite.m_vPos.x = m_fBackgroundTargetPosX;
	m_pBackgroundSprite.m_vPos.y = m_fBackgroundTargetPosY;
	m_pBackgroundSprite.m_fXScale = m_fBackgroundTargetScaleX;
	m_pBackgroundSprite.m_fYScale = m_fBackgroundTargetScaleY;

	m_pBarSprite.m_vPos.x = m_fBarTargetPosX;
	m_pBarSprite.m_vPos.y = m_fBarTargetPosY;
	m_pBarSprite.m_fXScale = m_fBarTargetScaleX;
	m_pBarSprite.m_fYScale = m_fBarTargetScaleY;
}

void UIWidgetResourceBar::InterpToTargets(float t) {
	m_pBackgroundSprite.m_vPos.x = m_pBackgroundSprite.m_vPos.x + (m_fBackgroundTargetPosX - m_pBackgroundSprite.m_vPos.x) * t;
	m_pBackgroundSprite.m_vPos.y = m_pBackgroundSprite.m_vPos.y + (m_fBackgroundTargetPosY - m_pBackgroundSprite.m_vPos.y) * t;
	m_pBackgroundSprite.m_fXScale = m_pBackgroundSprite.m_fXScale + (m_fBackgroundTargetScaleX - m_pBackgroundSprite.m_fXScale) * t;
	m_pBackgroundSprite.m_fYScale = m_pBackgroundSprite.m_fYScale + (m_fBackgroundTargetScaleY - m_pBackgroundSprite.m_fYScale) * t;

	m_pBarSprite.m_vPos.x = m_pBarSprite.m_vPos.x + (m_fBarTargetPosX - m_pBarSprite.m_vPos.x) * t;
	m_pBarSprite.m_vPos.y = m_pBarSprite.m_vPos.y + (m_fBarTargetPosY - m_pBarSprite.m_vPos.y) * t;
	m_pBarSprite.m_fXScale = m_pBarSprite.m_fXScale + (m_fBarTargetScaleX - m_pBarSprite.m_fXScale) * t;
	m_pBarSprite.m_fYScale = m_pBarSprite.m_fYScale + (m_fBarTargetScaleY - m_pBarSprite.m_fYScale) * t;
}