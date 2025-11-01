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
	
	m_pRenderer->GetSize((UINT)eSprite::HealthbarBackground, w, h);
	m_pRogueHealthBar.SetSprite(eSprite::HealthbarBackground, w, h);
	m_pRenderer->GetSize((UINT)eSprite::Healthbar, w, h);
	m_pRogueHealthBar.SetBarSprite(eSprite::Healthbar, w, h);

	m_pRenderer->GetSize((UINT)eSprite::HealthbarBackground, w, h);
	m_pWarriorHealthBar.SetSprite(eSprite::HealthbarBackground, w, h);
	m_pRenderer->GetSize((UINT)eSprite::Healthbar, w, h);
	m_pWarriorHealthBar.SetBarSprite(eSprite::Healthbar, w, h);

	m_pRenderer->GetSize((UINT)eSprite::HealthbarBackground, w, h);
	m_pDruidHealthBar.SetSprite(eSprite::HealthbarBackground, w, h);
	m_pRenderer->GetSize((UINT)eSprite::Healthbar, w, h);
	m_pDruidHealthBar.SetBarSprite(eSprite::Healthbar, w, h);

	m_pRenderer->GetSize((UINT)eSprite::ManabarBackground, w, h);
	m_pDruidManaBar.SetSprite(eSprite::ManabarBackground, w, h);
	m_pRenderer->GetSize((UINT)eSprite::Manabar, w, h);
	m_pDruidManaBar.SetBarSprite(eSprite::Manabar, w, h);

	m_fPosZ = m_pCamera->GetPos().z + m_fZOffset;
	charSelected = m_pPlayerManager->GetCharSelected();
	
	CalcFramesTargets();
	CalcResourceBarsTargets();
	CalcAbilitiesTargets();
}

void CUIManager::CalcFramesTargets() {
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

void CUIManager::CalcResourceBarsTargets() {
	float scaleX = 0;
	float scaleY = 0;
	Vector3 pos = Vector3(0.0f, 0.0f, 0.0f);
	float remaining = 0.0f;

	switch (charSelected) {
	case eCharSelected::Rogue:
		scaleX = 1 / (m_pRogueHealthBar.GetSizeX() / m_fLargeBarWidth);
		scaleY = 1 / (m_pRogueHealthBar.GetSizeY() / m_fLargeBarHeight);
		pos.x = m_pRogueFrame.m_fTargetPosX + (m_pRogueFrame.GetSizeX() * m_pRogueFrame.m_fTargetScaleX / 2) + (m_pRogueHealthBar.GetSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pRogueFrame.m_fTargetPosY - (m_pRogueFrame.GetSizeY() * m_pRogueFrame.m_fTargetScaleY / 2) + (m_pRogueHealthBar.GetSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pRogueHealthBar.SetTargets(scaleX, scaleY, pos);
		remaining = m_pPlayerManager->GetHealth();
		scaleX = scaleX * remaining;
		pos.x = m_pRogueFrame.m_fTargetPosX + (m_pRogueFrame.GetSizeX() * m_pRogueFrame.m_fTargetScaleX / 2) + (m_pRogueHealthBar.GetBarSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pRogueFrame.m_fTargetPosY - (m_pRogueFrame.GetSizeY() * m_pRogueFrame.m_fTargetScaleY / 2) + (m_pRogueHealthBar.GetBarSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pRogueHealthBar.SetBarTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pWarriorHealthBar.GetSizeX() / m_fSmallBarWidth);
		scaleY = 1 / (m_pWarriorHealthBar.GetSizeY() / m_fSmallBarHeight);
		pos.x = m_pWarriorFrame.m_fTargetPosX + (m_pWarriorFrame.GetSizeX() * m_pWarriorFrame.m_fTargetScaleX / 2) + (m_pWarriorHealthBar.GetSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pWarriorFrame.m_fTargetPosY - (m_pWarriorFrame.GetSizeY() * m_pWarriorFrame.m_fTargetScaleY / 2) + (m_pWarriorHealthBar.GetSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pWarriorHealthBar.SetTargets(scaleX, scaleY, pos);
		remaining = m_pPlayerManager->GetHealth();
		scaleX = scaleX * remaining;
		pos.x = m_pWarriorFrame.m_fTargetPosX + (m_pWarriorFrame.GetSizeX() * m_pWarriorFrame.m_fTargetScaleX / 2) + (m_pWarriorHealthBar.GetBarSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pWarriorFrame.m_fTargetPosY - (m_pWarriorFrame.GetSizeY() * m_pWarriorFrame.m_fTargetScaleY / 2) + (m_pWarriorHealthBar.GetBarSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pWarriorHealthBar.SetBarTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pDruidHealthBar.GetSizeX() / m_fSmallBarWidth);
		scaleY = 1 / (m_pDruidHealthBar.GetSizeY() / m_fSmallBarHeight);
		pos.x = m_pDruidFrame.m_fTargetPosX + (m_pDruidFrame.GetSizeX() * m_pDruidFrame.m_fTargetScaleX / 2) + (m_pDruidHealthBar.GetSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pDruidFrame.m_fTargetPosY - (m_pDruidFrame.GetSizeY() * m_pDruidFrame.m_fTargetScaleY / 2) + (m_pDruidHealthBar.GetSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pDruidHealthBar.SetTargets(scaleX, scaleY, pos);
		remaining = m_pPlayerManager->GetHealth();
		scaleX = scaleX * remaining;
		pos.x = m_pDruidFrame.m_fTargetPosX + (m_pDruidFrame.GetSizeX() * m_pDruidFrame.m_fTargetScaleX / 2) + (m_pDruidHealthBar.GetBarSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pDruidFrame.m_fTargetPosY - (m_pDruidFrame.GetSizeY() * m_pDruidFrame.m_fTargetScaleY / 2) + (m_pDruidHealthBar.GetBarSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pDruidHealthBar.SetBarTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pDruidManaBar.GetSizeX() / m_fSmallBarWidth);
		scaleY = 1 / (m_pDruidManaBar.GetSizeY() / m_fSmallBarHeight);
		pos.x = m_pDruidFrame.m_fTargetPosX + (m_pDruidFrame.GetSizeX() * m_pDruidFrame.m_fTargetScaleX / 2) + (m_pDruidManaBar.GetSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pDruidHealthBar.m_fTargetPosY + (m_pDruidHealthBar.GetSizeY() * m_pDruidHealthBar.m_fTargetScaleY / 2) + (m_pDruidManaBar.GetSizeY() * scaleY / 2) -(m_fIconToIconOffset / 2);
		pos.z = m_fPosZ;
		m_pDruidManaBar.SetTargets(scaleX, scaleY, pos);
		remaining = m_pPlayerManager->GetMana();
		scaleX = scaleX * remaining;
		pos.x = m_pDruidFrame.m_fTargetPosX + (m_pDruidFrame.GetSizeX() * m_pDruidFrame.m_fTargetScaleX / 2) + (m_pDruidManaBar.GetBarSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pDruidHealthBar.m_fTargetPosY + (m_pDruidHealthBar.GetSizeY() * m_pDruidHealthBar.m_fTargetScaleY / 2) + (m_pDruidManaBar.GetBarSizeY() * scaleY / 2) - (m_fIconToIconOffset / 2);
		pos.z = m_fPosZ;
		m_pDruidManaBar.SetBarTargets(scaleX, scaleY, pos);
		break;
	case eCharSelected::Warrior:
		scaleX = 1 / (m_pRogueHealthBar.GetSizeX() / m_fSmallBarWidth);
		scaleY = 1 / (m_pRogueHealthBar.GetSizeY() / m_fSmallBarHeight);
		pos.x = m_pRogueFrame.m_fTargetPosX + (m_pRogueFrame.GetSizeX() * m_pRogueFrame.m_fTargetScaleX / 2) + (m_pRogueHealthBar.GetSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pRogueFrame.m_fTargetPosY - (m_pRogueFrame.GetSizeY() * m_pRogueFrame.m_fTargetScaleY / 2) + (m_pRogueHealthBar.GetSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pRogueHealthBar.SetTargets(scaleX, scaleY, pos);
		remaining = m_pPlayerManager->GetHealth();
		scaleX = scaleX * remaining;
		pos.x = m_pRogueFrame.m_fTargetPosX + (m_pRogueFrame.GetSizeX() * m_pRogueFrame.m_fTargetScaleX / 2) + (m_pRogueHealthBar.GetBarSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pRogueFrame.m_fTargetPosY - (m_pRogueFrame.GetSizeY() * m_pRogueFrame.m_fTargetScaleY / 2) + (m_pRogueHealthBar.GetBarSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pRogueHealthBar.SetBarTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pWarriorHealthBar.GetSizeX() / m_fLargeBarWidth);
		scaleY = 1 / (m_pWarriorHealthBar.GetSizeY() / m_fLargeBarHeight);
		pos.x = m_pWarriorFrame.m_fTargetPosX + (m_pWarriorFrame.GetSizeX() * m_pWarriorFrame.m_fTargetScaleX / 2) + (m_pWarriorHealthBar.GetSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pWarriorFrame.m_fTargetPosY - (m_pWarriorFrame.GetSizeY() * m_pWarriorFrame.m_fTargetScaleY / 2) + (m_pWarriorHealthBar.GetSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pWarriorHealthBar.SetTargets(scaleX, scaleY, pos);
		remaining = m_pPlayerManager->GetHealth();
		scaleX = scaleX * remaining;
		pos.x = m_pWarriorFrame.m_fTargetPosX + (m_pWarriorFrame.GetSizeX() * m_pWarriorFrame.m_fTargetScaleX / 2) + (m_pWarriorHealthBar.GetBarSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pWarriorFrame.m_fTargetPosY - (m_pWarriorFrame.GetSizeY() * m_pWarriorFrame.m_fTargetScaleY / 2) + (m_pWarriorHealthBar.GetBarSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pWarriorHealthBar.SetBarTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pDruidHealthBar.GetSizeX() / m_fSmallBarWidth);
		scaleY = 1 / (m_pDruidHealthBar.GetSizeY() / m_fSmallBarHeight);
		pos.x = m_pDruidFrame.m_fTargetPosX + (m_pDruidFrame.GetSizeX() * m_pDruidFrame.m_fTargetScaleX / 2) + (m_pDruidHealthBar.GetSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pDruidFrame.m_fTargetPosY - (m_pDruidFrame.GetSizeY() * m_pDruidFrame.m_fTargetScaleY / 2) + (m_pDruidHealthBar.GetSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pDruidHealthBar.SetTargets(scaleX, scaleY, pos);
		remaining = m_pPlayerManager->GetHealth();
		scaleX = scaleX * remaining;
		pos.x = m_pDruidFrame.m_fTargetPosX + (m_pDruidFrame.GetSizeX() * m_pDruidFrame.m_fTargetScaleX / 2) + (m_pDruidHealthBar.GetBarSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pDruidFrame.m_fTargetPosY - (m_pDruidFrame.GetSizeY() * m_pDruidFrame.m_fTargetScaleY / 2) + (m_pDruidHealthBar.GetBarSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pDruidHealthBar.SetBarTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pDruidManaBar.GetSizeX() / m_fSmallBarWidth);
		scaleY = 1 / (m_pDruidManaBar.GetSizeY() / m_fSmallBarHeight);
		pos.x = m_pDruidFrame.m_fTargetPosX + (m_pDruidFrame.GetSizeX() * m_pDruidFrame.m_fTargetScaleX / 2) + (m_pDruidManaBar.GetSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pDruidHealthBar.m_fTargetPosY + (m_pDruidHealthBar.GetSizeY() * m_pDruidHealthBar.m_fTargetScaleY / 2) + (m_pDruidManaBar.GetSizeY() * scaleY / 2) - (m_fIconToIconOffset / 2);
		pos.z = m_fPosZ;
		m_pDruidManaBar.SetTargets(scaleX, scaleY, pos);
		remaining = m_pPlayerManager->GetMana();
		scaleX = scaleX * remaining;
		pos.x = m_pDruidFrame.m_fTargetPosX + (m_pDruidFrame.GetSizeX() * m_pDruidFrame.m_fTargetScaleX / 2) + (m_pDruidManaBar.GetBarSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pDruidHealthBar.m_fTargetPosY + (m_pDruidHealthBar.GetSizeY() * m_pDruidHealthBar.m_fTargetScaleY / 2) + (m_pDruidManaBar.GetBarSizeY() * scaleY / 2) - (m_fIconToIconOffset / 2);
		pos.z = m_fPosZ;
		m_pDruidManaBar.SetBarTargets(scaleX, scaleY, pos);
		break;
	case eCharSelected::Druid:
		scaleX = 1 / (m_pRogueHealthBar.GetSizeX() / m_fSmallBarWidth);
		scaleY = 1 / (m_pRogueHealthBar.GetSizeY() / m_fSmallBarHeight);
		pos.x = m_pRogueFrame.m_fTargetPosX + (m_pRogueFrame.GetSizeX() * m_pRogueFrame.m_fTargetScaleX / 2) + (m_pRogueHealthBar.GetSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pRogueFrame.m_fTargetPosY - (m_pRogueFrame.GetSizeY() * m_pRogueFrame.m_fTargetScaleY / 2) + (m_pRogueHealthBar.GetSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pRogueHealthBar.SetTargets(scaleX, scaleY, pos);
		remaining = m_pPlayerManager->GetHealth();
		scaleX = scaleX * remaining;
		pos.x = m_pRogueFrame.m_fTargetPosX + (m_pRogueFrame.GetSizeX() * m_pRogueFrame.m_fTargetScaleX / 2) + (m_pRogueHealthBar.GetBarSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pRogueFrame.m_fTargetPosY - (m_pRogueFrame.GetSizeY() * m_pRogueFrame.m_fTargetScaleY / 2) + (m_pRogueHealthBar.GetBarSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pRogueHealthBar.SetBarTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pWarriorHealthBar.GetSizeX() / m_fSmallBarWidth);
		scaleY = 1 / (m_pWarriorHealthBar.GetSizeY() / m_fSmallBarHeight);
		pos.x = m_pWarriorFrame.m_fTargetPosX + (m_pWarriorFrame.GetSizeX() * m_pWarriorFrame.m_fTargetScaleX / 2) + (m_pWarriorHealthBar.GetSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pWarriorFrame.m_fTargetPosY - (m_pWarriorFrame.GetSizeY() * m_pWarriorFrame.m_fTargetScaleY / 2) + (m_pWarriorHealthBar.GetSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pWarriorHealthBar.SetTargets(scaleX, scaleY, pos);
		remaining = m_pPlayerManager->GetHealth();
		scaleX = scaleX * remaining;
		pos.x = m_pWarriorFrame.m_fTargetPosX + (m_pWarriorFrame.GetSizeX() * m_pWarriorFrame.m_fTargetScaleX / 2) + (m_pWarriorHealthBar.GetBarSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pWarriorFrame.m_fTargetPosY - (m_pWarriorFrame.GetSizeY() * m_pWarriorFrame.m_fTargetScaleY / 2) + (m_pWarriorHealthBar.GetBarSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pWarriorHealthBar.SetBarTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pDruidHealthBar.GetSizeX() / m_fLargeBarWidth);
		scaleY = 1 / (m_pDruidHealthBar.GetSizeY() / m_fLargeBarHeight);
		pos.x = m_pDruidFrame.m_fTargetPosX + (m_pDruidFrame.GetSizeX() * m_pDruidFrame.m_fTargetScaleX / 2) + (m_pDruidHealthBar.GetSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pDruidFrame.m_fTargetPosY - (m_pDruidFrame.GetSizeY() * m_pDruidFrame.m_fTargetScaleY / 2) + (m_pDruidHealthBar.GetSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pDruidHealthBar.SetTargets(scaleX, scaleY, pos);
		remaining = m_pPlayerManager->GetHealth();
		scaleX = scaleX * remaining;
		pos.x = m_pDruidFrame.m_fTargetPosX + (m_pDruidFrame.GetSizeX() * m_pDruidFrame.m_fTargetScaleX / 2) + (m_pDruidHealthBar.GetBarSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pDruidFrame.m_fTargetPosY - (m_pDruidFrame.GetSizeY() * m_pDruidFrame.m_fTargetScaleY / 2) + (m_pDruidHealthBar.GetBarSizeY() * scaleY / 2);
		pos.z = m_fPosZ;
		m_pDruidHealthBar.SetBarTargets(scaleX, scaleY, pos);

		scaleX = 1 / (m_pDruidManaBar.GetSizeX() / m_fLargeBarWidth);
		scaleY = 1 / (m_pDruidManaBar.GetSizeY() / m_fLargeBarHeight);
		pos.x = m_pDruidFrame.m_fTargetPosX + (m_pDruidFrame.GetSizeX() * m_pDruidFrame.m_fTargetScaleX / 2) + (m_pDruidManaBar.GetSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pDruidHealthBar.m_fTargetPosY + (m_pDruidHealthBar.GetSizeY() * m_pDruidHealthBar.m_fTargetScaleY / 2) + (m_pDruidManaBar.GetSizeY() * scaleY / 2) - (m_fIconToIconOffset / 2);
		pos.z = m_fPosZ;
		m_pDruidManaBar.SetTargets(scaleX, scaleY, pos);
		remaining = m_pPlayerManager->GetMana();
		scaleX = scaleX * remaining;
		pos.x = m_pDruidFrame.m_fTargetPosX + (m_pDruidFrame.GetSizeX() * m_pDruidFrame.m_fTargetScaleX / 2) + (m_pDruidManaBar.GetBarSizeX() * scaleX / 2) - m_fIconToIconOffset;
		pos.y = m_pDruidHealthBar.m_fTargetPosY + (m_pDruidHealthBar.GetSizeY() * m_pDruidHealthBar.m_fTargetScaleY / 2) + (m_pDruidManaBar.GetBarSizeY() * scaleY / 2) - (m_fIconToIconOffset / 2);
		pos.z = m_fPosZ;
		m_pDruidManaBar.SetBarTargets(scaleX, scaleY, pos);
		break;
	}
}

void CUIManager::CalcAbilitiesTargets() {
}

void CUIManager::MoveUI(float t) {
	m_fPosZ = m_pCamera->GetPos().z + m_fZOffset;
	charSelected = m_pPlayerManager->GetCharSelected();

	CalcFramesTargets();
	CalcResourceBarsTargets();
	CalcAbilitiesTargets();

	if (m_pPlayerManager->IsSwitchingChar()) {
		m_pRogueFrame.InterpToTargets(t * m_fCharSwitchSpeed);
		m_pWarriorFrame.InterpToTargets(t * m_fCharSwitchSpeed);
		m_pDruidFrame.InterpToTargets(t * m_fCharSwitchSpeed);

		m_pRogueHealthBar.InterpToTargets(t * m_fCharSwitchSpeed);
		m_pRogueHealthBar.InterpBarToTargets(t * m_fCharSwitchSpeed);

		m_pWarriorHealthBar.InterpToTargets(t * m_fCharSwitchSpeed);
		m_pWarriorHealthBar.InterpBarToTargets(t * m_fCharSwitchSpeed);

		m_pDruidHealthBar.InterpToTargets(t * m_fCharSwitchSpeed);
		m_pDruidHealthBar.InterpBarToTargets(t * m_fCharSwitchSpeed);

		m_pDruidManaBar.InterpToTargets(t * m_fCharSwitchSpeed);
		m_pDruidManaBar.InterpBarToTargets(t * m_fCharSwitchSpeed);
	}
	else {
		m_pRogueFrame.SetToTargets();
		m_pWarriorFrame.SetToTargets();
		m_pDruidFrame.SetToTargets();

		m_pRogueHealthBar.SetToTargets();
		m_pRogueHealthBar.SetBarToTargets();

		m_pWarriorHealthBar.SetToTargets();
		m_pWarriorHealthBar.SetBarToTargets();

		m_pDruidHealthBar.SetToTargets();
		m_pDruidHealthBar.SetBarToTargets();

		m_pDruidManaBar.SetToTargets();
		m_pDruidManaBar.SetBarToTargets();
	}
}

void CUIManager::DrawUI() {
	m_pRenderer->Draw(&m_pRogueFrame.GetSprite());
	m_pRenderer->Draw(&m_pWarriorFrame.GetSprite());
	m_pRenderer->Draw(&m_pDruidFrame.GetSprite());

	m_pRenderer->Draw(&m_pRogueHealthBar.GetSprite());
	m_pRenderer->Draw(&m_pRogueHealthBar.GetBarSprite());

	m_pRenderer->Draw(&m_pWarriorHealthBar.GetSprite());
	m_pRenderer->Draw(&m_pWarriorHealthBar.GetBarSprite());

	m_pRenderer->Draw(&m_pDruidHealthBar.GetSprite());
	m_pRenderer->Draw(&m_pDruidHealthBar.GetBarSprite());

	m_pRenderer->Draw(&m_pDruidManaBar.GetSprite());
	m_pRenderer->Draw(&m_pDruidManaBar.GetBarSprite());
}