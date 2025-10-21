#include "UIWidgetAbility.h"

void UIWidgetAbility::SetBarSprite(UINT index, const LSpriteRenderer* m_pRenderer) {
	m_pBarSprite.m_nSpriteIndex = index;
	m_pBarSprite.m_fAlpha = 0.9f;
	m_pRenderer->GetSize(index, m_fBarSpriteSizeX, m_fBarSpriteSizeY);
}

void UIWidgetAbility::InterpToTargets(float t) {
	m_pBackgroundSprite.m_vPos.x = m_pBackgroundSprite.m_vPos.x + (m_fBackgroundTargetPosX - m_pBackgroundSprite.m_vPos.x) * t;
	m_pBackgroundSprite.m_vPos.y = m_pBackgroundSprite.m_vPos.y + (m_fBackgroundTargetPosY - m_pBackgroundSprite.m_vPos.y) * t;
	m_pBackgroundSprite.m_fXScale = m_pBackgroundSprite.m_fXScale + (m_fBackgroundTargetScaleX - m_pBackgroundSprite.m_fXScale) * t;
	m_pBackgroundSprite.m_fYScale = m_pBackgroundSprite.m_fYScale + (m_fBackgroundTargetScaleY - m_pBackgroundSprite.m_fYScale) * t;

	m_pBarSprite.m_vPos.x = m_pBarSprite.m_vPos.x + (m_fBarTargetPosX - m_pBarSprite.m_vPos.x) * t;
	m_pBarSprite.m_fXScale = m_pBarSprite.m_fXScale + (m_fBarTargetScaleX - m_pBarSprite.m_fXScale) * t;

	m_pBarSprite.m_vPos.y = m_fInitialPosY + (m_fBarTargetPosY - m_fInitialPosY) * t;
	m_pBarSprite.m_fYScale = m_fInitialScaleY + (m_fBarTargetScaleY - m_fInitialScaleY) * t;
}

void UIWidgetAbility::CalcTargets(float m_fFrameTargetPosX, float m_fFrameTargetPosY, float m_fTargetWidth, float m_fTargetHeight) {
	m_fBackgroundTargetScaleX = 1 / (m_fBackgroundSpriteSizeX / m_fTargetWidth);
	m_fBackgroundTargetScaleY = 1 / (m_fBackgroundSpriteSizeY / m_fTargetHeight);

	m_fBarTargetScaleX = 1 / (m_fBarSpriteSizeX / m_fTargetWidth);
	m_fBarTargetScaleY = m_fBarTargetScaleY = 0.0f;

	m_fBackgroundTargetPosX = m_fFrameTargetPosX - (m_fBackgroundSpriteSizeX * m_fBackgroundTargetScaleX / 2);
	m_fBackgroundTargetPosY = m_fFrameTargetPosY + (m_fBackgroundSpriteSizeY * m_fBackgroundTargetScaleY / 2);

	m_fBarTargetPosX = m_fFrameTargetPosX - (m_fBarSpriteSizeX * m_fBarTargetScaleX / 2);
	m_fBarTargetPosY = m_fFrameTargetPosY;
}

void UIWidgetAbility::AbilityPressed(float time, float m_fCooldown) {
	m_pBarSprite.m_fYScale = m_pBarSprite.m_fXScale;
	m_pBarSprite.m_vPos = Vector2(m_fBarTargetPosX, m_fBarTargetPosY + (m_fBarSpriteSizeY * m_fBarTargetScaleX / 2));

	m_fInitialPosY = m_pBarSprite.m_vPos.y;
	m_fInitialScaleY = m_pBarSprite.m_fYScale;

	m_fPressedTime = time;
}