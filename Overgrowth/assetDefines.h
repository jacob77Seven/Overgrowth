#ifndef ASSETDEFINES_H
#define ASSETDEFINES_H

enum class eSprite {
    background,
    healthbar,
    healthbarbackground,
    LyingPinkSquare,
    manabar,
    manabarbackground,
    PinkSquare,
    SylvaraTest,
    textwheel,
    Size
};

enum class eSound {
    clang,
    oink,
    sound-test,
    untitled,
    Size
};

string spriteHandles[9] = {"background", "healthbar", "healthbarbackground", "LyingPinkSquare", "manabar", "manabarbackground", "PinkSquare", "SylvaraTest", "textwheel"};

string soundHandles[4] = {"clang", "oink", "sound-test", "untitled"};

#endif // ASSETDEFINES_H
