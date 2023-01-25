#include <iostream>

#include "PixelRenderer/Texture.hpp"
#include "PixelRenderer/Renderer.hpp"

using namespace std;

namespace PixelRenderer {

    Texture::Texture(const int& width, const int& height, const int& channel, TextureManager* manager, const LoadInfo& info)
    :width(width), height(height), channel(channel), manager(manager), info(info) {
            data.resize(width * height);
        }

    Texture::~Texture() {
        data.clear();
        if (manager) manager->removeTexture(this);
    }

    const std::vector<Color>& Texture::getData() const {
        return data;
    }

    Color& Texture::at(const int& x, const int& y) {
        return data.at(y * width + x);
    }
}