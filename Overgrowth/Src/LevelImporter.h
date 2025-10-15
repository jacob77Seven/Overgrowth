#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "json.hpp"

#include "Defines.h"
#include "Abort.h"

#include "WindowDesc.h"
#include "Settings.h"
#include "Component.h"
#include "ComponentIncludes.h"
#include "Helpers.h"



struct TileData {
	int tileID;          // LDtk tile ID ("t")
	int srcX, srcY;      // Source rect in the tileset image ("src")
	int posX, posY;      // World position in pixels ("px")
	float posZ = 0.0f;   // Z position for layering
};

struct EntityData {
	std::string name;   // e.g. "Pig"
	float posX;
	float posY;
	float posZ;
};

struct LevelData {
	float val;
	std::vector<TileData> tiles;
	std::vector<EntityData> entities;
};

class LevelImporter: public LSettingsManager {

private:
	void ParseLevel(std::string LevelPath);

public:
	LevelImporter();
	void Load(size_t index, const char* name);
	//std::vector<LevelData> Levels;
	LevelData CurrLevel;
	LevelData GetLevelData();
};