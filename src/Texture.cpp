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

    //VectorTexture

    #ifdef PR_SVG
    VectorTexture::~VectorTexture() {
        if (target) delete target;
    }

    Texture* VectorTexture::render(const int& width, const int& height) {
        bitmap.reset(width, height);
        bitmap.clear(0x00000000);

        lunasvg::Matrix matrix(width / doc->width(), 0, 0, height / doc->height(), 0, 0);
        doc->render(bitmap, matrix);
        bitmap.convertToRGBA();

        target->width = width;
        target->height = height;
        target->data.resize(width * height);

        Color c;
        size_t raw = 0;
        uint8_t* data = bitmap.data();
        for (size_t i = 0; i < width * height; i++) {
            c.r = data[raw];
            c.g = data[raw + 1];
            c.b = data[raw + 2];
            c.a = data[raw + 3];
            raw += 4;

            target->data.at(i) = c;
        }

        return target;
    }
    #endif
}