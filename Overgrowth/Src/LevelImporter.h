#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "json.hpp"

struct TileData {
	int tileID;          // LDtk tile ID ("t")
	int srcX, srcY;      // Source rect in the tileset image ("src")
	int posX, posY;      // World position in pixels ("px")
};

struct LevelData {
	float val;
	std::vector<TileData> tiles;
};

class LevelImporter {
public:
	LevelImporter();
	LevelData ParseLevel(std::string LevelPath);
};