#include "UIWidgetResourceBar.h"

void UIWidgetResourceBar::SetBarTargets(float scaleX, float scaleY, Vector3 pos) {
	m_fBarTargetScaleX = scaleX;
	m_fBarTargetScaleY = scaleY;

	m_fBarTargetPosX = pos.x;
	m_fBarTargetPosY = pos.y;
	m_fBarTargetPosZ = pos.z;
}

void UIWidgetResourceBar::SetBarToTargets() {
	m_pBarSprite.m_fXScale = m_fBarTargetScaleX;
	m_pBarSprite.m_fYScale = m_fBarTargetScaleY;

	m_pBarSprite.m_vPos.x = m_fBarTargetPosX;
	m_pBarSprite.m_vPos.y = m_fBarTargetPosY;
	m_pBarSprite.m_vPos.z = m_fBarTargetPosZ;
}
void UIWidgetResourceBar::InterpBarToTargets(float t) {
	m_pBarSprite.m_fXScale = m_pBarSprite.m_fXScale + (m_fBarTargetScaleX - m_pBarSprite.m_fXScale) * t;
	m_pBarSprite.m_fYScale = m_pBarSprite.m_fYScale + (m_fBarTargetScaleY - m_pBarSprite.m_fYScale) * t;

	m_pBarSprite.m_vPos.x = m_pBarSprite.m_vPos.x + (m_fBarTargetPosX - m_pBarSprite.m_vPos.x) * t;
	m_pBarSprite.m_vPos.y = m_pBarSprite.m_vPos.y + (m_fBarTargetPosY - m_pBarSprite.m_vPos.y) * t;
	m_pBarSprite.m_vPos.z = m_fBarTargetPosZ;
}

void UIWidgetResourceBar::SetBarSprite(eSprite sprite, float w, float h) {
	m_pBarSprite.m_nSpriteIndex = (UINT)sprite;
	m_fBarSpriteSizeX = w;
	m_fBarSpriteSizeY = h;
}