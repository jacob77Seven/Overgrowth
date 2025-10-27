#include "LevelImporter.h"
#include <fstream>

#include "Common.h"
#include "ObjectManager.h"
#include "TestCharacter.h"


using json = nlohmann::json;

LevelImporter::LevelImporter() {
    printf("LevelImporter was Created.\n");
}

void LevelImporter::ParseLevel(std::string LevelPath) {
    LevelData lvlDat;

    // Load JSON file
    std::ifstream file(LevelPath);
    if (!file.is_open()) {
        printf("Failed to open level file: %s\n", LevelPath.c_str());
        return;
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

                if (layerName == "CollisionTiles" || layerName == "Decor" || layerName == "Entities") t.posZ = 0.0f;
                else if (layerName == "Background") t.posZ = 500.0f;
				else if (layerName == "Foreground") t.posZ = -500.0f;

                lvlDat.tiles.push_back(t);
            }
        }
        if (layer.contains("entityInstances")) {
            printf("Layer has entities. \n");
            for (auto& ent : layer["entityInstances"]) {
                EntityData e;
                e.name = ent["__identifier"];
                e.posX = ent["__worldX"];
                e.posY = (float)ent["__worldY"] * -1 + 750; // same Y inversion logic
				//if (layerName == "BackgroundEntities1") e.posZ = 500.0f;
				//else if (layerName == "Background2Entities") e.posZ = 750.0f;
				//else if (layerName == "ForegroundEntities") e.posZ = -500.0f;
				//else e.posZ = 0.0f;
                e.posZ = 0.0f;

                lvlDat.entities.push_back(e);

                printf("Entity '%s' at (%.1f, %.1f)\n", e.name.c_str(), e.posX, e.posY);
            }
        }
    }

    printf("Imported %zu tiles total.\n", lvlDat.tiles.size());
    CurrLevel = lvlDat;
    SpawnEntities();
}

void LevelImporter::SpawnEntities() {
    for (auto& e : CurrLevel.entities) {
        if (e.name == "Pig") {
            auto pigWeak = OCommon::m_pObjectManager->create<TestCharacter>(
                Vector3(e.posX, e.posY, e.posZ)
            );
            printf("Spawned Pig at (%.1f, %.1f, %.1f)\n", e.posX, e.posY, e.posZ);
            if (auto pig = pigWeak.lock()) {
                pig->SetObjectCollisionType(ECollisionType::Dynamic);
            }
        }
    }
}




void LevelImporter::Load(size_t index, const char* name) {
    if (m_pXmlSettings == nullptr)
        ABORT("Cannot access gamesettings.xml.");

    XMLElement* pLevelsTag = m_pXmlSettings->FirstChildElement("levels"); //sprites tag

    if (pLevelsTag == nullptr)
        ABORT("Cannot find <sounds> tag in gamesettings.xml");

    std::string path(pLevelsTag->Attribute("path")); //get path

    XMLElement* pLevelTag = pLevelsTag->FirstChildElement("sound");

    while (pLevelTag != nullptr && strcmp(name, pLevelTag->Attribute("name")))
        pLevelTag = pLevelTag->NextSiblingElement("sound");

    if (pLevelTag == nullptr)
        ABORT("Cannot find <sound> tag with name \"%s\".\n", name);

    const int instances = std::max(1, pLevelTag->IntAttribute("instances")); //get number of instances

    const std::string filename = path + "\\" + pLevelTag->Attribute("file");

    printf("%s\n", filename.c_str());

    //wchar_t* wfilename = nullptr; //wide file name
    //MakeWideFileName(filename.c_str(), wfilename); //convert the former to the latter
    ParseLevel(filename);
    //m_pSound[index].m_pSoundEffect = new SoundEffect(m_pAudioEngine, wfilename);
    //delete[] wfilename;

    //if (m_pSound[index].m_pSoundEffect == nullptr)
    //    ABORT("Cannot load sound \"%s\".\n", name);

    //createInstances(index, instances, SoundEffectInstance_Use3D |
        //SoundEffectInstance_ReverbUseFilters);
} //LoadByIndex

LevelData LevelImporter::GetLevelData() {
    return CurrLevel;
}