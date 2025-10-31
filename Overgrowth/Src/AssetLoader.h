#pragma once

#include "..\GameDefines.h"
#include "Renderer.h"
#include "Common.h"
#include "Component.h"
#include "SpriteDesc.h"
#include "ComponentIncludes.h"
//#include <iostream>

class OAssetLoader : OCommon, OAssetDefines, public LComponent {
public:
    OAssetLoader();
    void LoadSprites();
    void LoadSounds();
protected:
    std::string SpriteSheetJsonDirectory;

};