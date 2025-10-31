#include "../GameDefines.h"

#include "UIManager.h"
#include "Settings.h"
#include "ComponentIncludes.h"

void CUIManager::InitializeUI() {
	float w, h = 0;

	m_pRenderer->GetSize((UINT)eSprite::RogueCharFrame, w, h);
	m_pRogueFrame.SetSprite(eSprite::RogueCharFrame, w, h);

	m_vCameraPos = m_pCamera->GetPos();

	CalcFrameTargets();
	CalcHealthbarsTargets();
	CalcAbilitiesTargets();
	MoveUI();
}

void CUIManager::CalcFrameTargets() {
	float scaleX = 0;
	float scaleY = 0;
	Vector3 pos = Vector3(0.0f, 0.0f, 0.0f);

	scaleX = 1 / (m_pRogueFrame.GetSizeX() / m_fLargeIconHeight);
	scaleY = 1 / (m_pRogueFrame.GetSizeY() / m_fLargeIconHeight);
	pos.x = m_vCameraPos.x + m_fLargeIconXOffset;
	pos.y = m_vCameraPos.y + m_fLargeIconYOffset;
	pos.z = m_vCameraPos.z + m_fZOffset;
	m_pRogueFrame.SetTargets(scaleX, scaleY, pos);
}

void CUIManager::CalcHealthbarsTargets() {
}

void CUIManager::CalcAbilitiesTargets() {
}

void CUIManager::MoveUI() {
	
	m_pRogueFrame.SetToTargets();
}

void CUIManager::DrawUI() {
	m_vCameraPos = m_pCamera->GetPos();

	CalcFrameTargets();
	CalcHealthbarsTargets();
	CalcAbilitiesTargets();
	MoveUI();

	m_pRenderer->Draw(&m_pRogueFrame.GetSprite());
}