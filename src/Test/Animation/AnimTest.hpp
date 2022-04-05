#include <iostream>
#include <string>

#include "PixelRenderer/Renderer.hpp"
#include "PixelRenderer/Font.hpp"
#include "PixelRenderer/Texture.hpp"

class AnimationTest {
    private:
        Renderer* renderer;
        FontManager* fontMan;
        TextureManager* textureMan;
        Font* robotoFont;
        Font* futureFont;
        Texture* cross, *check;
    
        //Animation parts
        void renderShapes(const int& image);
        void renderTextures(const int& image);
        void renderBlending(const int& image);
        void renderRepetition(const int& image);
        void renderFonts(const int& image);

        //Internal methods
        std::string getFilename(const int& image);
        bool saveImage(const int& image);
        bool createImageFolder();
        void renderNothing(const int& image) {} //just for safety
        bool initRenderer();
        void cleanup();
        bool createVideo();
        bool createVideoParts(const int& partCount);

    public:
        int onExecute();
};

/**
 * Util class to use math functions like sinus and cosinus
 * in a range of 30/60 frames (30/60 frames equal 2π)
 */ 
class Functions {
    private:
        static const double pi;
        static const double pi2;
    public:
        /**
         * sine with variable periodic range
         */ 
        static double sin(const int& image, const int& range);

        /**
         * cosine with variable periodic range
         */ 
        static double cos(const int& image, const int& range);

        /**
         * linear range between 0 and 1 (can become > 1 for images greater than the given range)
         */ 
        static double linUp(const int& image, const int& range);

        /**
         * linear range between 1 and 0 (can become < 0 for images greater than the given range)
         */ 
        static double linDown(const int& image, const int& range);
};