#include "../GameDefines.h"

#include "UIManager.h"
#include "PlayerManager.h"

void CUIManager::InitializeUI() {
	float w, h = 0;
	m_pRenderer->GetSize((UINT)eSprite::RogueCharFrame, w, h);
	m_pRogueFrame.SetSprite(eSprite::RogueCharFrame, w, h);

	m_pRenderer->GetSize((UINT)eSprite::WarriorCharFrame, w, h);
	m_pWarriorFrame.SetSprite(eSprite::WarriorCharFrame, w, h);

	m_pRenderer->GetSize((UINT)eSprite::DruidCharFrame, w, h);
	m_pDruidFrame.SetSprite(eSprite::DruidCharFrame, w, h);

	m_fPosZ = m_pCamera->GetPos().z + m_fZOffset;
	charSelected = m_pPlayerManager->GetCharSelected();
	
	CalcFrameTargets();
	CalcHealthbarsTargets();
	CalcAbilitiesTargets();
}

void CUIManager::CalcFrameTargets() {
	float scaleX = 0;
	float scaleY = 0;
	Vector3 pos = Vector3(0.0f, 0.0f, 0.0f);

	switch (charSelected) {
	case eCharSelected::Rogue:
		scaleX = 1 / (m_pRogueFrame.GetSizeX() / m_fLargeIconHeight);
		scaleY = 1 / (m_pRogueFrame.GetSizeY() / m_fLargeIconHeight);
		pos.x = m_fLargeIconXOffset;
		pos.y = m_fLargeIconYOffset;
		pos.z = m_fPosZ;
		m_pRogueFrame.SetTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pWarriorFrame.GetSizeX() / m_fSmallIconHeight);
		scaleY = 1 / (m_pWarriorFrame.GetSizeY() / m_fSmallIconHeight);
		pos.x = m_fSmallIconXOffset;
		pos.y = pos.y - (m_pRogueFrame.GetSizeY() * m_pRogueFrame.m_fTargetScaleY / 2) - (m_pWarriorFrame.GetSizeY() * scaleY / 2) + m_fIconToIconOffset;
		pos.z = m_fPosZ;
		m_pWarriorFrame.SetTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pDruidFrame.GetSizeX() / m_fSmallIconHeight);
		scaleY = 1 / (m_pDruidFrame.GetSizeY() / m_fSmallIconHeight);
		pos.x = m_fSmallIconXOffset;
		pos.y = pos.y - (m_pWarriorFrame.GetSizeY() * m_pWarriorFrame.m_fTargetScaleY / 2) - (m_pDruidFrame.GetSizeY() * scaleY / 2) + m_fIconToIconOffset;
		pos.z = m_fPosZ;
		m_pDruidFrame.SetTargets(scaleX, scaleY, pos);
		break;
	case eCharSelected::Warrior:
		scaleX = 1 / (m_pRogueFrame.GetSizeX() / m_fSmallIconHeight);
		scaleY = 1 / (m_pRogueFrame.GetSizeY() / m_fSmallIconHeight);
		pos.x = m_fSmallIconXOffset;
		pos.y = m_fSmallIconYOffset;
		pos.z = m_fPosZ;
		m_pRogueFrame.SetTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pWarriorFrame.GetSizeX() / m_fLargeIconHeight);
		scaleY = 1 / (m_pWarriorFrame.GetSizeY() / m_fLargeIconHeight);
		pos.x = m_fLargeIconXOffset;
		pos.y = pos.y - (m_pRogueFrame.GetSizeY() * m_pRogueFrame.m_fTargetScaleY / 2) - (m_pWarriorFrame.GetSizeY() * scaleY / 2) + m_fIconToIconOffset;
		pos.z = m_fPosZ;
		m_pWarriorFrame.SetTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pDruidFrame.GetSizeX() / m_fSmallIconHeight);
		scaleY = 1 / (m_pDruidFrame.GetSizeY() / m_fSmallIconHeight);
		pos.x = m_fSmallIconXOffset;
		pos.y = pos.y - (m_pWarriorFrame.GetSizeY() * m_pWarriorFrame.m_fTargetScaleY / 2) - (m_pDruidFrame.GetSizeY() * scaleY / 2) + m_fIconToIconOffset;
		pos.z = m_fPosZ;
		m_pDruidFrame.SetTargets(scaleX, scaleY, pos);
		break;
	case eCharSelected::Druid:
		scaleX = 1 / (m_pRogueFrame.GetSizeX() / m_fSmallIconHeight);
		scaleY = 1 / (m_pRogueFrame.GetSizeY() / m_fSmallIconHeight);
		pos.x = m_fSmallIconXOffset;
		pos.y = m_fSmallIconYOffset;
		pos.z = m_fPosZ;
		m_pRogueFrame.SetTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pWarriorFrame.GetSizeX() / m_fSmallIconHeight);
		scaleY = 1 / (m_pWarriorFrame.GetSizeY() / m_fSmallIconHeight);
		pos.x = m_fSmallIconXOffset;
		pos.y = pos.y - (m_pRogueFrame.GetSizeY() * m_pRogueFrame.m_fTargetScaleY / 2) - (m_pWarriorFrame.GetSizeY() * scaleY / 2) + m_fIconToIconOffset;
		pos.z = m_fPosZ;
		m_pWarriorFrame.SetTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pDruidFrame.GetSizeX() / m_fLargeIconHeight);
		scaleY = 1 / (m_pDruidFrame.GetSizeY() / m_fLargeIconHeight);
		pos.x = m_fLargeIconXOffset;
		pos.y = pos.y - (m_pWarriorFrame.GetSizeY() * m_pWarriorFrame.m_fTargetScaleY / 2) - (m_pDruidFrame.GetSizeY() * scaleY / 2) + m_fIconToIconOffset;
		pos.z = m_fPosZ;
		m_pDruidFrame.SetTargets(scaleX, scaleY, pos);
		break;
	}
}

void CUIManager::CalcHealthbarsTargets() {
}

void CUIManager::CalcAbilitiesTargets() {
}

void CUIManager::MoveUI(float t) {
	m_fPosZ = m_pCamera->GetPos().z + m_fZOffset;
	charSelected = m_pPlayerManager->GetCharSelected();

	CalcFrameTargets();
	CalcHealthbarsTargets();
	CalcAbilitiesTargets();

	if (m_pPlayerManager->IsSwitchingChar()) {
		m_pRogueFrame.InterpToTargets(t * m_fCharSwitchSpeed);
		m_pWarriorFrame.InterpToTargets(t * m_fCharSwitchSpeed);
		m_pDruidFrame.InterpToTargets(t * m_fCharSwitchSpeed);
	}
	else {
		m_pRogueFrame.SetToTargets();
		m_pWarriorFrame.SetToTargets();
		m_pDruidFrame.SetToTargets();
	}

}

void CUIManager::DrawUI() {
	m_pRenderer->Draw(&m_pRogueFrame.GetSprite());
	m_pRenderer->Draw(&m_pWarriorFrame.GetSprite());
	m_pRenderer->Draw(&m_pDruidFrame.GetSprite());
}