#pragma once

#include "SpriteRenderer.h"

class ORenderer : public LSpriteRenderer {
private:
    UINT SheetSpriteSectionIndex;
public:
    void LoadTextureDescriptors(const std::vector<LTextureDesc*>& in_textures);
    ORenderer::ORenderer(eSpriteMode mode);
    //void LoadSpriteSheet(UINT index, const char* name, int sizex, int sizey, int numSprites);
    void SplitTextureFile(const char* filename, std::vector<LTextureDesc*>& out_textures, int split_cols, int split_rows);
};