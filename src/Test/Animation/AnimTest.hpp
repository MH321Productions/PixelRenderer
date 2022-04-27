#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "PixelRenderer/Renderer.hpp"
#include "PixelRenderer/Font.hpp"
#include "PixelRenderer/Texture.hpp"

class Part;

/**
 * Main Class for the animation
 */ 
class AnimationTest {
    private:
        std::vector<Part*> parts;

        //Internal methods
        std::string getFilename(const int& image);
        bool saveImage(const int& image);
        bool createImageFolder();
        bool initRenderer();
        void cleanup();
        bool createVideoParts();
        void registerPart(Part* part);

    public:
        Renderer* renderer;
        FontManager* fontMan;
        TextureManager* textureMan;
        Font* robotoFont;
        Font* futureFont;
        Texture* fruit, *check, *sprite;

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