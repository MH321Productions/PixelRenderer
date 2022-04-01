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

    public:
        int onExecute();
};

/**
 * Util class to use math functions like sinus and cosinus
 * in a range of 30/60 frames (30/60 frames equal 2π)
 */ 
class Functions {
    private:
        static const double full60;
        static const double full30;
        static const double pi;
        static const double pi2;
    public:
        /**
         * sine with periodic range of 60:
         * 0 -> 0
         * 15 -> 1
         * 30 -> 0
         * 45 -> -1
         * 60 -> 0
         */ 
        static double sin60(const int& image);
        
        /**
         * cosine with periodic range of 60:
         * 0 -> 1
         * 15 -> 0
         * 30 -> -1
         * 45 -> 0
         * 60 -> 1
         */ 
        static double cos60(const int& image);

        /**
         * sine with periodic range of 30:
         * 0 -> 0
         * 7 -> 1
         * 15 -> 0
         * 22 -> -1
         * 30 -> 0
         */ 
        static double sin30(const int& image);

        /**
         * cosine with periodic range of 30:
         * 0 -> 1
         * 7 -> 0
         * 15 -> -1
         * 22 -> 0
         * 30 -> 1
         */ 
        static double cos30(const int& image);

        /**
         * sine with variable periodic range
         */ 
        static double sin(const int& image, const int& range);

        /**
         * cosine with variable periodic range
         */ 
        static double cos(const int& image, const int& range);
};