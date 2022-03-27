#include <iostream>
#include <sstream>

#include "PixelRenderer/Font.hpp"

using namespace std;

//Globale ID initialisieren
int Font::globalId = 0;

Font::Font(const LoadInfo& info, FT_Library lib, FontManager* manager)
    : info(info), library(lib), width(0), height(0), isLoaded(false), hasUnicode(false), manager(manager) {
    
    //Id festlegen
    ostringstream str;
    str << globalId;
    id = str.str();
    globalId++;
    
    //Font laden
    if (!info.isValid()) {
        isLoaded = false;
        cerr << "Die LoadInfo ist ungültig und führt zu keinem Font" << endl;
        return;    
    }

    if (info.usePath()) {
        isLoaded = FontManager::checkFTError(
            FT_New_Face(library, info.path.c_str(), 0, &face),
            "Konnte Font " + id + " nicht öffnen"
        );
    } else if (info.useMemory()) {
        isLoaded = FontManager::checkFTError(
            FT_New_Memory_Face(library, info.data, info.size, 0, &face),
            "Konnte Font " + id + " nicht öffnen"
        );
    }
    

    //Wenn der Font geladen werden konnte, versuche auf Unicode zu setzen
    if (isLoaded) {
        hasUnicode = FontManager::checkFTError(
            FT_Select_Charmap(face, FT_ENCODING_UNICODE),
            "Der Font " + id + " kann nicht mit Unicode benutzt werden"
        );
    }
}

Font::~Font() {
    if (isLoaded) {
        FontManager::checkFTError(FT_Done_Face(face), "Konnte Font " + id + " nicht entladen");
    }

    if (manager != NULL) manager->removeFont(this);
}

bool Font::setSize(const int& width, const int& height) {
    this->width = width;
    this->height = height;

    return FontManager::checkFTError(
        FT_Set_Pixel_Sizes(face, width, height),
        "Konnte Font " + id + " nicht skalieren"
    );
}
