// AssetImporter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "tinyxml2.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <unordered_set>


using namespace tinyxml2;
using namespace std;
namespace fs = std::filesystem;

//std::cout << "Current working directory: " << fs::current_path() << std::endl;
/*fs::path GetExeFolder() {
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
}*/

int main() {
    //fs::path exeFolder = GetExeFolder();
    
    const string xmlPath = "../Media/XML/gamesettings.xml";
    const string imagesDir = "../Media/Images/";
    const string soundsDir = "../Media/Sounds/"; //sounds
    const string definesPath = "../Overgrowth/assetDefines.h";//assetDefines.h
    const string definesCPP = "../Overgrowth/assetDefines.cpp";//assetDefines.cpp
    
    //tryin find bug
     //arrays for the ENUM genertaor
    vector<string> spriteNames;
    vector<string> soundNames;
    

    //checking if directories there
    cout << "XML Path: " << xmlPath << endl;
    cout << "Images Directory" << imagesDir << endl;

    try {
        if (!fs::exists(imagesDir)) fs::create_directories(imagesDir);
        if (!fs::exists(soundsDir)) fs::create_directories(soundsDir);
        fs::path definesDir = fs::path(definesPath).parent_path();
        if (!fs::exists(definesDir)) fs::create_directories(definesDir);
    }
    catch (const fs::filesystem_error& e) {
        cerr << "Filesystem setup error: " << e.what() << endl;
        return 1;
    }



    tinyxml2::XMLDocument doc;
    XMLError err = doc.LoadFile(xmlPath.c_str());
    if (err != XML_SUCCESS) {
        cerr << "Error: could not load " << xmlPath << endl;
        return 1;
    }

    XMLElement* root = doc.RootElement();
    if (!root) {
        cerr << "Error: XML has no root element\n";
        return 1;
    }

    /*XMLElement* root = doc.FirstChildElement("settings");
    if (!root) {
        cerr << "<settings> root not found" << endl;
        return 1;
    }*/


    //---SPRITES
    XMLElement* spritesElem = root->FirstChildElement("sprites");
    if (!spritesElem) {
        //cerr << "Error: <sprites> section not found.\n";
        spritesElem = doc.NewElement("sprites");
        root->InsertEndChild(spritesElem);
    } 

    unordered_set<string> xmlSprites;
    for (XMLElement* spr = spritesElem->FirstChildElement("sprite"); spr; spr = spr->NextSiblingElement("sprite")) {
        const char* fileAttr = spr->Attribute("file");
        if (fileAttr) xmlSprites.insert(fileAttr);
    }

    // Add missing sprites
    for (auto& entry : fs::directory_iterator(imagesDir)) {
        if (!entry.is_regular_file()) continue;
        string ext = entry.path().extension().string();
        if (ext != ".png" && ext != ".jpg") continue;

        string fileName = entry.path().filename().string();
        string name = entry.path().stem().string();
        spriteNames.push_back(name);

        if (xmlSprites.find(fileName) == xmlSprites.end()) {
            XMLElement* newSprite = doc.NewElement("sprite");
            newSprite->SetAttribute("name", name.c_str());
            newSprite->SetAttribute("file", fileName.c_str());
            spritesElem->InsertEndChild(newSprite);
            cout << "[SpriteImporter] Added sprite: " << fileName << endl;
        }
    }

    // Remove missing sprite files
    for (XMLElement* spr = spritesElem->FirstChildElement("sprite"); spr;) {
        XMLElement* next = spr->NextSiblingElement("sprite");
        const char* fileAttr = spr->Attribute("file");
        if (fileAttr) {
            fs::path fullPath = fs::path(imagesDir) / fileAttr;
            if (!fs::exists(fullPath)) {
                cout << "[SpriteImporter] Removed missing sprite: " << fileAttr << endl;
                spritesElem->DeleteChild(spr);
            }
        }
        spr = next;
    }



    //---SOUNDS
    XMLElement* soundsElem = root->FirstChildElement("sounds");
    if (!soundsElem) {
        soundsElem = doc.NewElement("sounds");
        root->InsertEndChild(soundsElem);
    }

    unordered_set<string> xmlSounds;
    for (XMLElement* snd = soundsElem->FirstChildElement("sound"); snd; snd = snd->NextSiblingElement("sound")) {
        const char* fileAttr = snd->Attribute("file");
        if (fileAttr) xmlSounds.insert(fileAttr);
    }

    // Add missing sounds
    for (auto& entry : fs::directory_iterator(soundsDir)) {
        if (!entry.is_regular_file()) continue;
        string ext = entry.path().extension().string();
        if (ext != ".wav" && ext != ".mp3") continue;

        string fileName = entry.path().filename().string();
        string name = entry.path().stem().string();
        soundNames.push_back(name);

        if (xmlSounds.find(fileName) == xmlSounds.end()) {
            XMLElement* newSound = doc.NewElement("sound");
            newSound->SetAttribute("name", name.c_str());
            newSound->SetAttribute("file", fileName.c_str());
            soundsElem->InsertEndChild(newSound);
            cout << "[SpriteImporter] Added sound: " << fileName << endl;
        }
    }

    // Remove missing sounds
    for (XMLElement* snd = soundsElem->FirstChildElement("sound"); snd;) {
        XMLElement* next = snd->NextSiblingElement("sound");
        const char* fileAttr = snd->Attribute("file");
        if (fileAttr) {
            fs::path fullPath = fs::path(soundsDir) / fileAttr;
            if (!fs::exists(fullPath)) {
                cout << "[SpriteImporter] Removed missing sound: " << fileAttr << endl;
                soundsElem->DeleteChild(snd);
            }
        }
        snd = next;
    }




    //saving changes
    if (doc.SaveFile(xmlPath.c_str()) == XML_SUCCESS)
        cout << "gamesettings.xml updated successfully.\n";
    else
        cerr << "Error saving gamesettings.xml\n";

    //AssetDefines.h generator
    ofstream out(definesPath);
    if (!out.is_open()) {
        cerr << "Error: could not open " << definesPath << endl;
        return 1;
    }

    out << "#ifndef ASSETDEFINES_H\n#define ASSETDEFINES_H\n\n";
    out << "#include \"Defines.h\"\n";
    out << "#include <string>\n\n";
    // Sprites enum
    out << "enum class eSprite : UINT {\n";
    for (const auto& name : spriteNames) out << "    " << name << ",\n";
    out << "    Size\n};\n\n";

    // Sounds enum
    out << "enum class eSound : UINT {\n";
    for (const auto& name : soundNames) out << "    " << name << ",\n";
    out << "    Size\n};\n\n";

    out << "class OAssetDefines {\n";
    out << "protected:\n";

    out << "static std::string spriteHandles[";
    out << spriteNames.size() << "];\n";
    out << "static std::string soundHandles[";
    out << soundNames.size() << "];\n";
    out << "};\n\n";


    out << "#endif // ASSETDEFINES_H\n";
    out.close();
    cout << "[SpriteImporter] assetDefines.h generated successfully.\n";

    //creating assetDefines.h
    ofstream header(definesCPP);
    if (!header.is_open()) {
        cerr << "Error: could not open " << definesPath << endl;
        return 1;
    }

    header << "#include \"assetDefines.h\"\n\n";
    // Sprite handles array
    header << "std::string OAssetDefines::spriteHandles[" << spriteNames.size() << "] = {";
    for (size_t i = 0; i < spriteNames.size(); ++i) {
        header << "\"" << spriteNames[i] << "\"";
        if (i != spriteNames.size() - 1) header << ", ";
    }
    header << "};\n\n";

    // Sound handles array
    header << "std::string OAssetDefines::soundHandles[" << soundNames.size() << "] = {";
    for (size_t i = 0; i < soundNames.size(); ++i) {
        header << "\"" << soundNames[i] << "\"";
        if (i != soundNames.size() - 1) header << ", ";
    }
    header << "};\n\n";

    header.close();

    cout << "[SpriteImporter] assetDefines.cpp generated successfully.\n";


    
    return 0;
}
