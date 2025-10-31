#include "UIWidget.h"

void UIWidget::SetToTargets() {
	m_pSprite.m_fXScale = m_fTargetScaleX;
	m_pSprite.m_fYScale = m_fTargetScaleY;

	m_pSprite.m_vPos.x = m_fTargetPosX;
	m_pSprite.m_vPos.y = m_fTargetPosY;
	m_pSprite.m_vPos.z = m_fTargetPosZ;
}

void UIWidget::SetTargets(float scaleX, float scaleY, Vector3 pos) {
	m_fTargetScaleX = scaleX;
	m_fTargetScaleY = scaleY;

	m_fTargetPosX = pos.x;
	m_fTargetPosY = pos.y;
	m_fTargetPosZ = pos.z;
}

void UIWidget::SetSprite(eSprite sprite, float w, float h) {
	m_pSprite.m_nSpriteIndex = (UINT)sprite;
	m_fSpriteSizeX = w;
	m_fSpriteSizeY = h;
}