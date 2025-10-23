// SpriteImporter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "tinyxml2.h"
#include <filesystem>
#include <iostream>
#include <unordered_set>
#include <string>

using namespace tinyxml2;
using namespace std;
namespace fs = std::filesystem;

//std::cout << "Current working directory: " << fs::current_path() << std::endl;
fs::path GetExeFolder() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    return fs::path(buffer).parent_path();
}

// Scan a folder for files with specific extensions
vector<fs::path> ScanFolder(const fs::path& folder, const vector<string>& extensions) {
    vector<fs::path> results;
    if (!fs::exists(folder)) return results;

    for (auto& entry : fs::directory_iterator(folder)) {
        if (!entry.is_regular_file()) continue;
        string ext = entry.path().extension().string();
        for (auto& allowed : extensions) {
            if (_stricmp(ext.c_str(), allowed.c_str()) == 0) {
                results.push_back(entry.path());
            }
        }
    }
    return results;
}

int main() {
    fs::path exeFolder = GetExeFolder();
    
    const string xmlPath = "../Media/XML/gamesettings.xml";
    const string imagesDir = "../Media/Images/";
    const string soundsDir = "../Media/Sounds/"; //sounds
    const string definesPath = "../../Overgrowth/assetDefines.h";//assetDefines
    
    //tryin find bug
    
    cout << "XML Path: " << xmlPath << endl;
    cout << "Images Directory" << imagesDir << endl;

    XMLDocument doc;
    XMLError err = doc.LoadFile(xmlPath.c_str());
    if (err != XML_SUCCESS) {
        cerr << "Error: could not load " << xmlPath << endl;
        return 1;
    }

    /*XMLElement* root = doc.RootElement();
    if (!root) {
        cerr << "Error: XML has no root element\n";
        return 1;
    }*/

    XMLElement* root = doc.FirstChildElement("settings");
    if (!root) {
        cerr << "<settings> root not found" << endl;
        return 1;
    }

    //arrays for the ENUM genertaor
    unordered_set<string> spriteNames;
    unordered_set<string> soundNames;

    XMLElement* spritesElem = root->FirstChildElement("sprites");
    if (!spritesElem) {
        cerr << "Error: <sprites> section not found.\n";
    } else {
        string spritePath = spritesElem->Attribute("path");
        fs::path spriteDir = fs::path("../Overgrowth") / spritePath;

        //Yoinking all sprites in folder
        unordered_set<string> existingSprites;
        for (auto& entry : fs::directory_iterator(spriteDir)) {
            if (entry.is_regular_file()) {
                existingSprites.insert(entry.path().filename().string());
            }//if
        }//for

        //Remove missing sprites
        for (XMLElement* elem = spritesElem->FirstChildElement("sprite"); elem;) {
            XMLElement* next = elem->NextSiblingElement("sprite");
            const char* file = elem->Attribute("file");
            if (file && !existingSprites.count(file)) {
                cout << "Removing missing sprite: " << file << endl;
                spritesElem->DeleteChild(elem);
            }
            elem = next;
        }

        //Update with new sprites
        for (const auto& file : existingSprites) {
            bool exists = false;
            for (XMLElement* elem = spritesElem->FirstChildElement("sprite"); elem; elem = elem->NextSiblingElement("sprite")) {
                const char* xmlFile = elem->Attribute("file");
                if (xmlFile && file == xmlFile) {
                    exists = true;
                    break;
                }
            }

            if (!exists) {
                string name = file.substr(0, file.find('.'));
                XMLElement* newElem = doc.NewElement("sprite");
                newElem->SetAttribute("name", name.c_str());
                newElem->SetAttribute("file", file.c_str());
                spritesElem->InsertEndChild(newElem);
                cout << "Added new sprite: " << file << endl;
            }
        }//for

        //Grabbing handler for AssetDefines.h ENUM generator
        for (XMLElement* elem = spritesElem->FirstChildElement("sprite"); elem; elem = elem->NextSiblingElement("sprite")) {
            const char* name = elem->Attribute("name");
            if (name) spriteNames.insert(name);
        }

    }//else

    //---SOUNDS
    XMLElement* soundsElem = root->FirstChildElement("sounds");
    if (!soundsElem) {
        cerr << "Error: <sounds> section not found." << endl;
    } else {
        string soundPath = soundsElem->Attribute("path");
        fs::path soundDir = fs::path("../Overgrowth") / soundPath;

        unordered_set<string> existingSounds;
        for (auto& entry : fs::directory_iterator(soundDir)) {
            if (entry.is_regular_file()) {
                existingSounds.insert(entry.path().filename().string());
            }
        }

        // Remove missing sounds
        for (XMLElement* elem = soundsElem->FirstChildElement("sound"); elem;) {
            XMLElement* next = elem->NextSiblingElement("sound");
            const char* file = elem->Attribute("file");
            if (file && !existingSounds.count(file)) {
                cout << "Removing missing sound: " << file << endl;
                soundsElem->DeleteChild(elem);
            }
            elem = next;
        }

        // Add new sounds
        for (const auto& file : existingSounds) {
            bool exists = false;
            for (XMLElement* elem = soundsElem->FirstChildElement("sound"); elem; elem = elem->NextSiblingElement("sound")) {
                const char* xmlFile = elem->Attribute("file");
                if (xmlFile && file == xmlFile) {
                    exists = true;
                    break;
                }
            }

            if (!exists) {
                string name = file.substr(0, file.find('.'));
                XMLElement* newElem = doc.NewElement("sound");
                newElem->SetAttribute("name", name.c_str());
                newElem->SetAttribute("file", file.c_str());
                soundsElem->InsertEndChild(newElem);
                cout << "Added new sound: " << file << endl;
            }
        }//for

        //Grabbing handler for AssetDefines.h ENUM generator
        for (XMLElement* elem = soundsElem->FirstChildElement("sound"); elem; elem = elem->NextSiblingElement("sound")) {
            const char* name = elem->Attribute("name");
            if (name) soundNames.insert(name);
        }

    }//else
    
    if (doc.SaveFile(xmlPath.c_str()) == XML_SUCCESS)
        cout << "gamesettings.xml updated successfully.\n";
    else
        cerr << "Error saving gamesettings.xml\n";

    //AssetDefines.h generator
    ofstream out(definesPath);
    if (!out.is_open()) {
        std::cerr << "Error: Could not create " << definesPath << endl;
        return -1;
    }

    out << "/// \\file assetDefines.h\n";
    out << "/// \\brief Auto-generated asset definitions.\n\n";
    out << "#ifndef __ASSET_DEFINES_H__\n";
    out << "#define __ASSET_DEFINES_H__\n\n";
    out << "#include \"Defines.h\"\n";
    out << "#include \"Sound.h\"\n\n";

    // Sprites
    out << "enum class eSprite: UINT {\n";
    for (const auto& name : spriteNames)
        out << "  " << name << ",\n";
    out << "  Size // MUST BE LAST\n};\n\n";

    // Sounds
    out << "enum class eSound: UINT {\n";
    for (const auto& name : soundNames)
        out << "  " << name << ",\n";
    out << "  Size // MUST BE LAST\n};\n\n";

    //creating array of the handles
        // ---Sprites---
        out << "string spriteHandles[" << spriteNames.size() << "] = {";
        for (size_t i = 0; i < spriteNames.size(); ++i)
            if (i == spriteNames.size() - 1) {
                out << "\"" <<  spriteNames[i] << "\"" <<  "};" << endl;
            }
            else {
                out << "\"" << spriteNames[i] << "\"" << ", ";
            }

        // ---Sounds---
        out << "string soundHandles[" << soundNames.size() << "] = {";
        for (size_t i = 0; i < soundNames.size(); ++i)
            if (i == soundNames.size() - 1) {
                out << "\"" << soundNames[i] << "\"" << "};" << endl;
            }
            else {
                out << "\"" <<  soundNames[i] << "\"" << ", ";
            }

    out << "#endif // __ASSET_DEFINES_H__\n";

    out.close();
    cout << "Generated " << definesPath << " successfully.\n";

    
    return 0;
}
