#ifndef ASSETDEFINES_H
#define ASSETDEFINES_H

#include "Defines.h"
#include <string>

enum class eSprite : UINT {
    background,
    LyingPinkSquare,
    PinkSquare,
    PinkSquare2,
    SylvaraTest,
    textwheel,
    walkright,
    Size
};

enum class eSound : UINT {
    clang,
    oink,
    piano,
    Size
};

class OAssetDefines {
static std::string spriteHandles[7];
static std::string soundHandles[3];
};

#endif // ASSETDEFINES_H
