#include "LevelImporter.h"
LevelImporter::LevelImporter() {
	printf("LevelImporter was Created.\n");
}

LevelData LevelImporter::ParseLevel(std::string LevelPath) {
	LevelData lvlDat = { 1 };
	printf("Importing level %s\n", LevelPath.c_str());
	//printf("ParseLevel");
	return lvlDat;
}