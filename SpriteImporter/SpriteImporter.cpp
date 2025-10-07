// SpriteImporter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "tinyxml2.h"
#include <filesystem>
#include <iostream>
#include <unordered_set>
#include <string>

using namespace tinyxml2;
//using namespace std;
namespace fs = std::filesystem;

//std::cout << "Current working directory: " << fs::current_path() << std::endl;

int main() {
    const std::string xmlPath = "../Overgrowth/Media/XML/gamesettings.xml";
    const std::string imagesDir = "../Overgrowth/Media/Images/";


    XMLDocument doc;
    XMLError err = doc.LoadFile(xmlPath.c_str());
    if (err != XML_SUCCESS) {
        std::cerr << "Error: could not load " << xmlPath << std::endl;
        return 1;
    }

    XMLElement* root = doc.RootElement();
    if (!root) {
        std::cerr << "Error: XML has no root element\n";
        return 1;
    }

    XMLElement* spritesElem = root->FirstChildElement("sprites");
    if (!spritesElem) {
        std::cerr << "Error: No <sprites> element found\n";
        return 1;
    }

    // Collect all existing sprite file names from XML
    std::unordered_set<std::string> xmlSprites;
    for (XMLElement* spr = spritesElem->FirstChildElement("sprite"); spr; spr = spr->NextSiblingElement("sprite")) {
        const char* fileAttr = spr->Attribute("file");
        if (fileAttr)
            xmlSprites.insert(fileAttr);
    }

    // Scan directory for all .png/.jpg files
    for (auto& entry : fs::directory_iterator(imagesDir)) {
        if (!entry.is_regular_file()) continue;

        const auto& path = entry.path();
        std::string ext = path.extension().string();
        if (ext == ".png" || ext == ".jpg") {
            std::string fileName = path.filename().string();
            std::string name = path.stem().string();

            if (xmlSprites.find(fileName) == xmlSprites.end()) {
                // Add new sprite node
                XMLElement* newSprite = doc.NewElement("sprite");
                newSprite->SetAttribute("name", name.c_str());
                newSprite->SetAttribute("file", fileName.c_str());
                spritesElem->InsertEndChild(newSprite);
                std::cout << "Added sprite: " << fileName << std::endl;
            }
        }
    }

    // Remove missing files
    for (XMLElement* spr = spritesElem->FirstChildElement("sprite"); spr;) {
        XMLElement* next = spr->NextSiblingElement("sprite");
        const char* fileAttr = spr->Attribute("file");
        if (fileAttr) {
            fs::path fullPath = fs::path(imagesDir) / fileAttr;
            if (!fs::exists(fullPath)) {
                std::cout << "Removed missing sprite: " << fileAttr << std::endl;
                spritesElem->DeleteChild(spr);
            }
        }
        spr = next;
    }

    // Backup before saving
    fs::copy_file(xmlPath, xmlPath + ".bak", fs::copy_options::overwrite_existing);

    if (doc.SaveFile(xmlPath.c_str()) == XML_SUCCESS)
        std::cout << "gamesettings.xml updated successfully.\n";
    else
        std::cerr << "Error saving gamesettings.xml\n";

    return 0;
}
