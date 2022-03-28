#include <iostream>
#include <string>

#include "PixelRenderer/Renderer.hpp"
#include "PixelRenderer/Font.hpp"
#include "PixelRenderer/Texture.hpp"

Renderer* renderer;
FontManager* fontMan;
TextureManager* textureMan;

std::string getFilename(const int& image);