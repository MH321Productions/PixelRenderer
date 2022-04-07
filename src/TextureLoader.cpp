#include <iostream>
#include <stb_image.h>
#include <map>

#include "PixelRenderer/Texture.hpp"
#include "PixelRenderer/Renderer.hpp"

using namespace std;

Texture* Texture::loadTexture(const LoadInfo& info, TextureManager* manager) {
    int width, height, channels;

    if (!info.isValid()) {
        cerr << "The load info is invalid" << endl;
        return NULL;
    }

    rgb* stbiData;
    if (info.usePath()) {
        stbiData = stbi_load(info.path.c_str(), &width, &height, &channels, 4);
    } else if (info.useMemory()) {
       stbiData = stbi_load_from_memory(info.data, info.size, &width, &height, &channels, 4);
    }

    if (!stbiData) {
        cerr << "Couldn't load image: " << stbi_failure_reason() << endl;
        return NULL;
    }

    Texture* result = new Texture(width, height, channels, manager, info);

    int x = 0, y = 0, maxIndex = width * height * channels;
    Color c;
    if (channels == 4) {
        for (int index = 0; index < maxIndex; index+= 4) {
            c.r = stbiData[index];
            c.g = stbiData[index + 1];
            c.b = stbiData[index + 2];
            c.a = stbiData[index + 3];

            //Daten schreiben
            result->at(x, y) = c;
            x++;
            if (x == width) {
                x = 0;
                y++;
            }
        }
    } else { //3 Channel, alpha Wert immer 255
        c.a = 255;
        for (int index = 0; index < maxIndex; index+= 3) {
            c.r = stbiData[index];
            c.g = stbiData[index + 1];
            c.b = stbiData[index + 2];

            //Daten schreiben
            result->at(x, y) = c;
            x++;
            if (x == width) {
                x = 0;
                y++;
            }
        }
    }

    stbi_image_free(stbiData);

    return result;
}