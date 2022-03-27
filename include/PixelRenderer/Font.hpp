#pragma once

#include <string>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Loader.hpp"

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
         * Ändert die Größe des Fonts
         * @param width Die Breite in Pixeln
         * @param height Die Höhe in Pixeln
         * @returns Ob das Skalieren erfolgreich war
         */ 
        bool setSize(const int& width, const int& height);
        
        /**
         * Ändert die Größe des Fonts
         * @param size Die Größe (Breite und Höhe) in Pixeln
         * @returns Ob das Skalieren erfolgreich war
         */ 
        inline bool setSize(const int& size) {return setSize(size, size);}

        //entspricht isLoaded && hasUnicode
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
         * Prüft den Rückgabewert einer FreeType-Funktion und gibt bei Bedarf eine Fehlermeldung in cerr aus.
         * Diese Meldung hat folgendes Muster:
         * "<errorMessage>: <FreeType errorMessage>"
         * @param error Der Fehlercode, der von der FreeType-Funktion genereiert wurde
         * @param errorMessage Die Nachricht, die bei einem Fehler zusammen mit der Fehlermeldung geschrieben wird
         * (Standardmäßig "FreeType Fehler")
         * @returns Ob die Funktion fehlerfrei ausgeführt wurde (false bei irgendeinem Fehler)
         */ 
        static bool checkFTError(const int& error, const std::string& errorMessage = "FreeType Fehler");
};