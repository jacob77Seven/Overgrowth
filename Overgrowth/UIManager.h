#pragma once
#include "Common.h"

class CUIManager :
	public CCommon {
private:
    LSpriteDesc2D m_pRogueCharFrame;
    LSpriteDesc2D m_pWarriorCharFrame;
    LSpriteDesc2D m_pDruidCharFrame;
public:
    void InitializeUI();
    void DrawUI();
};