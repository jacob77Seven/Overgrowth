#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include "tinyxml2.h"
#include <windows.h>

namespace fs = std::filesystem;
using namespace tinyxml2;

//Utility to make valid C++ enum names
std::string sanitizeName(const std::string& name) {
    std::string clean = name;
    for (char& c : clean) {
        if (!isalnum(c)) c = '_'; // replace non-alphanumeric with _
    }
    return clean;
}

std::vector<std::string> parseElements(XMLElement* parent, const char* elementTag) {
    std::vector<std::string> names;
    for (XMLElement* elem = parent->FirstChildElement(elementTag);
         elem != nullptr;
         elem = elem->NextSiblingElement(elementTag)) {
        const char* name = elem->Attribute("name");
        if (name)
            names.push_back(sanitizeName(name));
    }
    return names;
}

int main() {
    try {
        //Locate exe and project paths
        wchar_t buffer[MAX_PATH];
        GetModuleFileNameW(NULL, buffer, MAX_PATH);
        fs::path exePath = fs::path(buffer).parent_path();

        //check path for modification
        fs::path xmlPath = exePath / "../Overgrowth/Media/XML/gamesettings.xml";
        fs::path outputPath = exePath / "../Overgrowth/assetDefines.h";

        xmlPath = fs::weakly_canonical(xmlPath);
        outputPath = fs::weakly_canonical(outputPath);

        std::cout << "Using XML: " << xmlPath << "\n";
        std::cout << "Output File: " << outputPath << "\n";

        //Load XML
        XMLDocument doc;
        if (doc.LoadFile(xmlPath.string().c_str()) != XML_SUCCESS) {
            std::cerr << "ERROR: Could not load XML file.\n";
            return 1;
        }

        XMLElement* root = doc.FirstChildElement("settings");
        if (!root) {
            std::cerr << "ERROR: No <settings> root found.\n";
            return 1;
        }

        //Parse sprites
        XMLElement* sprites = root->FirstChildElement("sprites");
        std::vector<std::string> spriteNames;
        if (sprites)
            spriteNames = parseElements(sprites, "sprite");

        // 4️⃣ Parse sounds
        XMLElement* sounds = root->FirstChildElement("sounds");
        std::vector<std::string> soundNames;
        if (sounds)
            soundNames = parseElements(sounds, "sound");

        // 5️⃣ Write assetDefines.h
        std::ofstream out(outputPath);
        if (!out.is_open()) {
            std::cerr << "ERROR: Could not open output file for writing.\n";
            return 1;
        }

        out << "/// \\file assetDefines.h\n";
        out << "/// \\brief Auto-generated from gamesettings.xml. DO NOT EDIT BY HAND.\n\n";
        out << "#ifndef __AUTO_ASSET_DEFINES__\n";
        out << "#define __AUTO_ASSET_DEFINES__\n\n";
        out << "#include \"Defines.h\"\n";
        out << "#include \"Sound.h\"\n\n";

        // --- eSprite ---
        out << "/// \\brief Sprite enumerated type (auto-generated)\n";
        out << "enum class eSprite : UINT {\n";
        for (size_t i = 0; i < spriteNames.size(); ++i)
            out << "    " << spriteNames[i] << (i < spriteNames.size() - 1 ? "," : "") << "\n";
        out << "    ,Size // MUST BE LAST\n";
        out << "}; // eSprite\n\n";

        // --- eSound ---
        out << "/// \\brief Sound enumerated type (auto-generated)\n";
        out << "enum class eSound : UINT {\n";
        for (size_t i = 0; i < soundNames.size(); ++i)
            out << "    " << soundNames[i] << (i < soundNames.size() - 1 ? "," : "") << "\n";
        out << "    ,Size // MUST BE LAST\n";
        out << "}; // eSound\n\n";

        out << "#endif // __AUTO_ASSET_DEFINES__\n";
        out.close();

        std::cout << "Generated assetDefines.h successfully.\n";
        std::cout << "Sprites: " << spriteNames.size()
                  << " | Sounds: " << soundNames.size() << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
