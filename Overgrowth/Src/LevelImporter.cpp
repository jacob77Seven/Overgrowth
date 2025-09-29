#include "LevelImporter.h"
#include <fstream>

using json = nlohmann::json;

LevelImporter::LevelImporter() {
    printf("LevelImporter was Created.\n");
}

LevelData LevelImporter::ParseLevel(std::string LevelPath) {
    LevelData lvlDat;

    // Load JSON file
    std::ifstream file(LevelPath);
    if (!file.is_open()) {
        printf("Failed to open level file: %s\n", LevelPath.c_str());
        return lvlDat;
    }

    json j;
    file >> j;

    // Get first level (for now)
    auto level = j["levels"][0];

    // Iterate through layer instances
    for (auto& layer : level["layerInstances"]) {
        std::string layerName = layer["__identifier"];
        printf("Parsing Layer: %s\n", layerName.c_str());

        // Only process tile layers for now
        if (layer.contains("gridTiles")) {
            for (auto& tile : layer["gridTiles"]) {
                TileData t;

                // Tile ID
                t.tileID = tile["t"];

                // Source rect inside tileset
                t.srcX = tile["src"][0];
                t.srcY = tile["src"][1];

                // World position (px array has [x,y])
                t.posX = tile["px"][0];
				t.posY = (tile["px"][1]) * -1 + 750; // Invert Y for our coordinate system

                lvlDat.tiles.push_back(t);
            }
        }
    }

    printf("Imported %zu tiles total.\n", lvlDat.tiles.size());
    return lvlDat;
}