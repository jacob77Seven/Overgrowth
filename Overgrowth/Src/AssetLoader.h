#pragma once

#include "..\GameDefines.h"
#include "Renderer.h"
#include "Common.h"
#include "Component.h"
#include "SpriteDesc.h"
#include "ComponentIncludes.h"
//#include <iostream>

class OAssetLoader : OCommon {
public:
    OAssetLoader();
    void LoadSprites();
protected:
    std::string SpriteSheetJsonDirectory = "Media\\json\\.json";
};