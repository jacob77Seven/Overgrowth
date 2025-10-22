#pragma once

#include "SpriteRenderer.h"

class ORenderer : public LSpriteRenderer {
private:
    UINT SheetSpriteSectionIndex;
    UINT ImageFilesSectionNum;
    UINT SheetSpriteSectionNum;

public:
    void LoadTextureDescriptors(const std::vector<LTextureDesc*>& in_textures);
    ORenderer::ORenderer(eSpriteMode mode);
    //void LoadSpriteSheet(UINT index, const char* name, int sizex, int sizey, int numSprites);
    void LoadSpriteSheet(UINT index, const char* name, int sizex, int sizey, int numSprites);
    
    void Initialize(UINT NumSpriteFiles, UINT NumSpriteSheetSprites) {
        LSpriteRenderer::Initialize(NumSpriteFiles + NumSpriteSheetSprites);
        SheetSpriteSectionIndex = NumSpriteFiles;
        ImageFilesSectionNum = NumSpriteFiles;
        SheetSpriteSectionNum = NumSpriteSheetSprites;
    };
};