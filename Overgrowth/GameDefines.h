/// \file GameDefines.h
/// \brief Game specific defines.

#ifndef __L4RC_GAME_GAMEDEFINES_H__
#define __L4RC_GAME_GAMEDEFINES_H__

#include "Defines.h"
#include "Sound.h"

/// \brief Sprite enumerated type.
///
/// An enumerated type for the sprites, which will be cast to an unsigned
/// integer and used for the index of the corresponding texture in graphics
/// memory. `Size` must be last.

enum class eSprite: UINT{
  Background, TextWheel, Pig, Pink_sheet, PinkSquare, walkright,
  RogueCharFrame, WarriorCharFrame, DruidCharFrame, HealthbarBackground, Healthbar, ManabarBackground, Manabar, AbilityCooldown,
  RogueAbilityOne, RogueAbilityTwo, RogueAbilityThree,
  WarriorAbilityOne, WarriorAbilityTwo, WarriorAbilityThree,
  DruidAbilityOne, DruidAbilityTwo, DruidAbilityThree,
  Size  //MUST BE LAST
}; //eSprite


enum class eLevels : UINT {
	TestLevel, RealLevel,
	Size  //MUST BE LAST
}; //eSprite


/// \brief Sound enumerated type.
///
/// An enumerated type for the sounds, which will be cast to an unsigned
/// integer and used for the index of the corresponding sample. `Size` must 
/// be last.

enum class eSound: UINT{
  Clang, Grunt, Oink, Piano,
  Size  //MUST BE LAST
}; //eSound

enum class eInput : UINT {
	KeyOne, KeyTwo, KeyThree, KeyW, KeyA, KeyS, KeyD, KeyQ, KeyE, KeyR,
	Size
};

#endif //__L4RC_GAME_GAMEDEFINES_H__
