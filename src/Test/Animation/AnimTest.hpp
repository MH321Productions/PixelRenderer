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