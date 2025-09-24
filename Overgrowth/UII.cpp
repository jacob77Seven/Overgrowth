#include "Game.h"

#include "GameDefines.h"
#include "SpriteRenderer.h"
#include "ComponentIncludes.h"

void CGame::DrawUI() {
	m_pRenderer->Draw(eSprite::Rogue, Vector2(0, 0));
}