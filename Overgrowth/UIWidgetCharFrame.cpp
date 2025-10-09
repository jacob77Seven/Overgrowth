#include "UIWidgetCharFrame.h"

void UIWidgetCharFrame::SetSprite(UINT index, const LSpriteRenderer* m_pRenderer) {
	m_pSprite.m_nSpriteIndex = index;
	m_pRenderer->GetSize(index, m_fSpriteSizeX, m_fSpriteSizeY);
}

void UIWidgetCharFrame::SetToTargets() {
	m_pSprite.m_vPos.x = m_fTargetPosX;
	m_pSprite.m_vPos.y = m_fTargetPosY;
	m_pSprite.m_fXScale = m_fTargetScaleX;
	m_pSprite.m_fYScale = m_fTargetScaleY;
}

void UIWidgetCharFrame::InterpToTargets(float t) {
	m_pSprite.m_vPos.x = m_pSprite.m_vPos.x + (m_fTargetPosX - m_pSprite.m_vPos.x) * t;
	m_pSprite.m_vPos.y = m_pSprite.m_vPos.y + (m_fTargetPosY - m_pSprite.m_vPos.y) * t;
	m_pSprite.m_fXScale = m_pSprite.m_fXScale + (m_fTargetScaleX - m_pSprite.m_fXScale) * t;
	m_pSprite.m_fYScale = m_pSprite.m_fYScale + (m_fTargetScaleY - m_pSprite.m_fYScale) * t;
}

void UIWidgetCharFrame::CalcTargetPos(float m_fMaxHeight) {
	m_fTargetPosX = m_fSpriteSizeX * m_fTargetScaleX / 2;
	m_fTargetPosY = m_fMaxHeight - (m_fSpriteSizeY * m_fTargetScaleY / 2);
}

void UIWidgetCharFrame::CalcTargetScale(float m_fTargetHeight) {
	m_fTargetScaleX = 1 / (m_fSpriteSizeX / m_fTargetHeight);
	m_fTargetScaleY = 1 / (m_fSpriteSizeY / m_fTargetHeight);
}