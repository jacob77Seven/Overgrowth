// SpriteImporter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "tinyxml2.h"
#include <filesystem>
#include <iostream>
#include <unordered_set>
#include <string>
#include <windows.h>

using namespace tinyxml2;
using namespace std;
//using namespace std;
namespace fs = std::filesystem;

//cout << "Current working directory: " << fs::current_path() << endl;

int main() {
    try {
        // 1️⃣ Get the path to this executable
        fs::path exePath = fs::current_path(); // fallback in case get_path fails

        // On Windows: get the actual executable location
        #ifdef _WIN32
        wchar_t buffer[MAX_PATH];
        GetModuleFileNameW(NULL, buffer, MAX_PATH);
        exePath = fs::path(buffer).parent_path(); // folder where the exe lives
        #endif

        std::cout << "Importer running from: " << exePath << std::endl;

        // 2️⃣ Build paths relative to the executable
        fs::path xmlPath = exePath / "../Overgrowth/Media/XML/gamesettings.xml";
        fs::path imagesDir = exePath / "../Overgrowth/Media/Images";

        xmlPath = fs::weakly_canonical(xmlPath);
        imagesDir = fs::weakly_canonical(imagesDir);

        std::cout << "Resolved XML path: " << xmlPath << std::endl;
        std::cout << "Resolved Images path: " << imagesDir << std::endl;

        // 3️⃣ Try loading the XML
        XMLDocument doc;
        XMLError result = doc.LoadFile(xmlPath.string().c_str());

        if (result != XML_SUCCESS) {
            std::cerr << "ERROR: Could not load XML file: " << xmlPath << std::endl;
            std::cerr << "TinyXML2 error code: " << result << std::endl;
            return 1;
        }

        std::cout << "XML loaded successfully!\n";
    
        XMLDocument doc;
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
    
        XMLElement* spritesElem = root->FirstChildElement("sprites");
        if (!spritesElem) {
            cerr << "Error: No <sprites> element found\n";
            return 1;
        }
    
        // Collect all existing sprite file names from XML
        unordered_set<string> xmlSprites;
        for (XMLElement* spr = spritesElem->FirstChildElement("sprite"); spr; spr = spr->NextSiblingElement("sprite")) {
            const char* fileAttr = spr->Attribute("file");
            if (fileAttr)
                xmlSprites.insert(fileAttr);
        }

        // Scan directory for all .png/.jpg files
        for (auto& entry : fs::directory_iterator(imagesDir)) {
            if (!entry.is_regular_file()) continue;
    
            const auto& path = entry.path();
            string ext = path.extension().string();
            if (ext == ".png" || ext == ".jpg") {
                string fileName = path.filename().string();
                string name = path.stem().string();
    
                if (xmlSprites.find(fileName) == xmlSprites.end()) {
                    // Add new sprite node
                    XMLElement* newSprite = doc.NewElement("sprite");
                    newSprite->SetAttribute("name", name.c_str());
                    newSprite->SetAttribute("file", fileName.c_str());
                    spritesElem->InsertEndChild(newSprite);
                    cout << "Added sprite: " << fileName << endl;
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
                    cout << "Removed missing sprite: " << fileAttr << endl;
                    spritesElem->DeleteChild(spr);
                }
        }
        spr = next;
        }
    
        // Backup before saving
        fs::copy_file(xmlPath, xmlPath + ".bak", fs::copy_options::overwrite_existing);
    
        if (doc.SaveFile(xmlPath.c_str()) == XML_SUCCESS)
            cout << "gamesettings.xml updated successfully.\n";
        else
            cerr << "Error saving gamesettings.xml\n";

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }


    return 0;
}
