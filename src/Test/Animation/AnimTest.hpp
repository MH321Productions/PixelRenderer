#include <iostream>
#include <string>

#include "PixelRenderer/Renderer.hpp"
#include "PixelRenderer/Font.hpp"
#include "PixelRenderer/Texture.hpp"

//Renderer Components
static Renderer* renderer;
static FontManager* fontMan;
static TextureManager* textureMan;
static Font* robotoFont;
static Font* futureFont;

//Animation methods
void renderShapes(const int& image);
void renderTextures(const int& image);
void renderBlending(const int& image);
void renderRepetition(const int& image);
void renderFonts(const int& image);