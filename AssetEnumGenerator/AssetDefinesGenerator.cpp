#include "tinyxml2.h""
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace tinyxml2;
using namespace std;
namespace fs = std::filesystem;


//Utility to make valid C++ enum names
string sanitizeName(const string& name) {
    string clean = name;
    for (char& c : clean) {
        if (!isalnum(c)) c = '_'; // replace non-alphanumeric with _
    }
    return clean;
}

vector<string> parseElements(XMLElement* parent, const char* elementTag) {
    vector<string> names;
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

        //path for generalization
        fs::path xmlPath = exePath / "../../Media/XML/gamesettings.xml";
        fs::path outputPath = exePath / "../../Overgrowth/AssetDefines.h";

        xmlPath = fs::weakly_canonical(xmlPath);
        outputPath = fs::weakly_canonical(outputPath);

        cout << "XML Path: " << xmlPath << "\n";
        cout << "Output File: " << outputPath << "\n";

        //Load XML
        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(xmlPath.string().c_str()) != XML_SUCCESS) {
            cerr << "ERROR: Could not load XML file.\n";
            return 1;
        }

        XMLElement* root = doc.FirstChildElement("settings");
        if (!root) {
            cerr << "ERROR: No <settings> root found.\n";
            return 1;
        }

        //Parse sprites
        XMLElement* sprites = root->FirstChildElement("sprites");
        vector<string> spriteNames;
        if (sprites)
            spriteNames = parseElements(sprites, "sprite");

        // 4?? Parse sounds
        XMLElement* sounds = root->FirstChildElement("sounds");
        vector<string> soundNames;
        if (sounds)
            soundNames = parseElements(sounds, "sound");

        // 5?? Write assetDefines.h
        ofstream out(outputPath);
        if (!out.is_open()) {
            cerr << "ERROR: Could not open output file for writing.\n";
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


        //creating array of the handles
        // ---Sprites---
        out << "string spriteHandles[" << spriteNames.size() << "] = {";
        for (size_t i = 0; i < spriteNames.size(); ++i)
            if (i == spriteNames.size() - 1) {
                out << spriteNames[i] << "};" << endl;
            }
            else {
                out << spriteNames[i] << ", ";
            }

        // ---Sounds---
        out << "string soundHandles[" << soundNames.size() << "] = {";
        for (size_t i = 0; i < soundNames.size(); ++i)
            if (i == soundNames.size() - 1) {
                out << soundNames[i] << "};" << endl;
            }
            else {
                out << soundNames[i] << ", ";
            }


        out << "\n #endif // __AUTO_ASSET_DEFINES__\n";
        out.close();

        cout << "Generated assetDefines.h successfully.\n";
        cout << "Sprites: " << spriteNames.size()
            << " | Sounds: " << soundNames.size() << "\n";

    }
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
    return 0;
}