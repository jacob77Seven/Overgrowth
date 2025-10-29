//Animation Manager, in charge of 
#ifndef __L4RC_GAME_ANIMATIONMANAGER_H__
#define __L4RC_GAME_ANIMATIONMANAGER_H__

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include "nlohmann/json.hpp"

struct AnimationData {
	int startFrame;//beginning frame
	int endFrame;//ending frame
	int frameRate;
	string spriteSheet;//handler to grab from sheet
};

class Animator {
	AnimationManager();

	void LoadAnimation();


};

#endif