#pragma once

#include <string>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "PixelRenderer/Loader.hpp"

class FontManager;
class Renderer;
class LoadInfo;

class Font {
    friend class FontManager;
    friend class Renderer;
    private:
        static int globalId;

        LoadInfo info;
        std::string id;
        FT_Library library;
        FT_Face face;
        int width, height;
        FontManager* manager;

        Font(const LoadInfo& name, FT_Library lib, FontManager* manager);
    
    public:
        bool isLoaded;
        bool hasUnicode;

        ~Font();

        /**
         * Changes the size of the font
         * @param width The width (pixel)
         * @param height The height (pixel)
         * @returns If the scaling was successfull
         */ 
        bool setSize(const int& width, const int& height);
        
        /**
         * Changes the size of the font
         * @param size The width and height (pixel)
         * @returns If the scaling was successfull
         */ 
        inline bool setSize(const int& size) {return setSize(size, size);}

        //equivalent to: isLoaded && hasUnicode
        inline bool isReady() {return isLoaded && hasUnicode;}
};

class FontManager {
    friend class Font;
    private:
        std::vector<Font*> loadedFonts;
        bool blockRemoval = false;
        FT_Library library;

        void removeFont(Font* font);
    
    public:
        bool isInitialized = false;

        FontManager();
        ~FontManager();

        Font* getFont(const LoadInfo& info);

        /**
         * Checks the return value of a FreeType-function and sends an error message to cerr if needed.
         * The message looks like this:
         * "<errorMessage>: <FreeType errorMessage>"
         * @param error The return value of the function
         * @param errorMessage The message to send with the FreeType error message
         * (normally "FreeType error")
         * @returns If the function was executed successfully (any error returns false)
         */ 
        static bool checkFTError(const int& error, const std::string& errorMessage = "FreeType error");
};