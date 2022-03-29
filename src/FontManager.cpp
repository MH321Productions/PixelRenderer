#include <iostream>

#include "PixelRenderer/Font.hpp"

using namespace std;

FontManager::FontManager() {
    //FreeType initialisieren
    isInitialized = checkFTError(FT_Init_FreeType(&library), "Konnte FreeType nicht initialisieren");
}

FontManager::~FontManager() {
    blockRemoval = true;

    for (Font* f: loadedFonts) delete f;

    loadedFonts.clear();

    //FreeType stoppen
    checkFTError(FT_Done_FreeType(library), "Konnte FreeType nicht beenden");
}

void FontManager::removeFont(Font* font) {
    if (!blockRemoval) {
        for (vector<Font*>::iterator it = loadedFonts.begin(); it != loadedFonts.end(); it++) {
            if (*it == font) {
                loadedFonts.erase(it);
                break;
            }
        }
    }
}

Font* FontManager::getFont(const LoadInfo& info) {
    for (Font* f: loadedFonts) {
        if (f != NULL && f->info == info) return f;
    }

    Font* load = new Font(info, library, this);
    loadedFonts.push_back(load);

    return load;
}

bool FontManager::checkFTError(const int& error, const std::string& errorMessage) {
    if (error) {
        const char* msg = FT_Error_String(error);
        cerr << errorMessage << ": " << (msg ? msg : "") << endl;
        return false;
    }

    return true;
}