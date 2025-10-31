#include "AssetLoader.h"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

OAssetLoader::OAssetLoader()
{
    SpriteSheetJsonDirectory = "Media\\json\\SpriteSheetInfo.json";
}

void OAssetLoader::LoadSounds()
{
    m_pAudio->Initialize(eSound::Size);
    for (UINT i = 0; i < (UINT)eSound::Size; i++) {
        m_pAudio->Load(i, OAssetDefines::soundHandles[i].c_str());
    }
}

void OAssetLoader::LoadSprites()
{
    printf("AssetLoader::LoadSprites() start\n");

    // Load JSON file
    std::ifstream file(SpriteSheetJsonDirectory);
    if (!file.is_open()) {
        printf("Failed to open level file: %s\n", SpriteSheetJsonDirectory.c_str());
        return;
    }

    json j;
    try {
        file >> j;
    }
    catch (const char* e) {
        // Handle the exception
        printf("Exception caught: %s", e);
    }

    printf("AssetLoader::LoadSprites() JSON loaded\n");

    UINT TotalSpriteSheetSprites = 0;
    // Get first level (for now)
    //auto sheets = j["SpriteSheets"][0];
    // First we have to add up the number of sprites across all the sprite sheets so we can initialize enough room.
    for (auto& sheet : j["SpriteSheets"]) {
        TotalSpriteSheetSprites += sheet["NumSprites"];
    }
    // Now initialize the renderer.
    OCommon::m_pRenderer->Initialize((UINT)eSprite::Size, TotalSpriteSheetSprites);

    printf("AssetLoader::LoadSprites() Initialized\n");

    // Now we can finally load the sprites.
    OCommon::m_pRenderer->BeginResourceUpload();
    for (UINT i = 0; i < (UINT)eSprite::Size; i++) {
        OCommon::m_pRenderer->Load(i, OAssetDefines::spriteHandles[i].c_str());
    }

    printf("AssetLoader::LoadSprites() sprites loaded\n");

    // And sprite-sheet-sprites.
    for (auto& sheet : j["SpriteSheets"]) {
        std::string handle = static_cast<std::string>(sheet["SheetHandle"]);
        int NumSprites = sheet["NumSprites"];
        int SizeX = sheet["SizeX"];
        int SizeY = sheet["SizeY"];
        printf("SheetHandle: %s, SizeX: %d, SizeY: %d, NumSprites: %d\n", handle.c_str(), SizeX, SizeY, NumSprites);
        UINT index = OCommon::GetSpriteHandleIndex(handle);
        OCommon::m_pRenderer->LoadSpriteSheet(index, handle.c_str(), SizeX, SizeY, NumSprites);
    }

    printf("AssetLoader::LoadSprites() spritesheets loaded\n");

    OCommon::m_pRenderer->EndResourceUpload();



    for (UINT i = 0; i < (UINT)eSprite::Size; i++) {
        
    }
    // OCommon::m_pRenderer->Load

    printf("AssetLoader::LoadSprites() done\n");
}
