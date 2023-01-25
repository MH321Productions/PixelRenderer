#include <iostream>
#include <sstream>

#include "PixelRenderer/Font.hpp"

using namespace std;

namespace PixelRenderer {

    //init global id
    int Font::globalId = 0;

    Font::Font(const LoadInfo& info, FT_Library lib, FontManager* manager)
        : info(info), library(lib), width(0), height(0), isLoaded(false), hasUnicode(false), manager(manager) {
        
        //determine id
        ostringstream str;
        str << globalId;
        id = str.str();
        globalId++;
        
        //load font
        if (!info.isValid()) {
            isLoaded = false;
            cerr << "The load info is invalid" << endl;
            return;    
        }

        if (info.usePath()) {
            isLoaded = FontManager::checkFTError(
                FT_New_Face(library, info.path.c_str(), 0, &face),
                "Couldn't open font " + id
            );
        } else if (info.useMemory()) {
            isLoaded = FontManager::checkFTError(
                FT_New_Memory_Face(library, info.data, info.size, 0, &face),
                "Couldn't open font " + id
            );
        }
        

        //when the font is loaded, try to use unicode
        if (isLoaded) {
            hasUnicode = FontManager::checkFTError(
                FT_Select_Charmap(face, FT_ENCODING_UNICODE),
                "The font " + id + " doesn't support unicode"
            );
        }
    }

    Font::~Font() {
        if (isLoaded) {
            FontManager::checkFTError(FT_Done_Face(face), "Couldn't unload font " + id);
        }

        if (manager != NULL) manager->removeFont(this);
    }

    bool Font::setSize(const int& width, const int& height) {
        this->width = width;
        this->height = height;

        return FontManager::checkFTError(
            FT_Set_Pixel_Sizes(face, width, height),
            "Couldn't scale font " + id
        );
    }
}