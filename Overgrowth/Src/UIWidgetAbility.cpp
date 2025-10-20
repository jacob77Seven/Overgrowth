#include "UIWidgetAbility.h"

void UIWidgetAbility::CalcTargets(float m_fFrameTargetPosX, float m_fFrameTargetPosY, float m_fTargetWidth, float m_fTargetHeight) {
	m_fBackgroundTargetScaleX = 1 / (m_fBackgroundSpriteSizeX / m_fTargetWidth);
	m_fBackgroundTargetScaleY = 1 / (m_fBackgroundSpriteSizeY / m_fTargetHeight);

	m_fBarTargetScaleX = 1 / (m_fBarSpriteSizeX / m_fTargetWidth);
	m_fBarTargetScaleY = 1 / (m_fBarSpriteSizeY / m_fTargetHeight);

	float m_fBottomLeftCornerX = m_fFrameTargetPosX * 2;
	float m_fBottomLeftCornerY = m_fFrameTargetPosY - m_fFrameTargetPosX + (m_fBackgroundSpriteSizeY * m_fBackgroundTargetScaleX * 1.2);

	m_fBackgroundTargetPosX = m_fBottomLeftCornerX + (m_fBackgroundSpriteSizeX * m_fBackgroundTargetScaleX / 2);
	m_fBackgroundTargetPosY = m_fBottomLeftCornerY + (m_fBackgroundSpriteSizeY * m_fBackgroundTargetScaleY / 2);

	m_fBarTargetPosX = m_fBottomLeftCornerX + (m_fBarSpriteSizeX * m_fBarTargetScaleX / 2);
	m_fBarTargetPosY = m_fBottomLeftCornerY + (m_fBarSpriteSizeY * m_fBarTargetScaleY / 2);
}