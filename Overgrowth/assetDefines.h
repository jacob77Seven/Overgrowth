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
    walkleft,
    walkright,
    RogueCharFrame, WarriorCharFrame, DruidCharFrame, HealthbarBackground, Healthbar, ManabarBackground, Manabar, AbilityCooldown,
    RogueAbilityOne, RogueAbilityTwo, RogueAbilityThree,
    WarriorAbilityOne, WarriorAbilityTwo, WarriorAbilityThree,
    DruidAbilityOne, DruidAbilityTwo, DruidAbilityThree,
    Size
};

enum class eSound : UINT {
    clang,
    oink,
    piano,
    Size
};

class OAssetDefines {
protected:
static std::string spriteHandles[(UINT)eSprite::Size];
static std::string soundHandles[3];
};

#endif // ASSETDEFINES_H
