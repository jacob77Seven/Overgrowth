#pragma once
#include <string>
#include <iostream>
#include "json.hpp"

struct LevelData {
	float val;
};

class LevelImporter {
public:
	LevelImporter();
	LevelData ParseLevel(std::string LevelPath);
};