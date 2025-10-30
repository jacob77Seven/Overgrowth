#pragma once

#include "..\GameDefines.h"
#include "Renderer.h"
#include "Common.h"
#include "Component.h"
#include "SpriteDesc.h"
#include "ComponentIncludes.h"
//#include <iostream>

class OAssetLoader : OCommon, OAssetDefines {
public:
    OAssetLoader();
    void LoadSprites();
protected:
    std::string SpriteSheetJsonDirectory;

};