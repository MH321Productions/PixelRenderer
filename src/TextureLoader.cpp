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
        stbiData = stbi_load(info.path.c_str(), &width, &height, &channels, 0);
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
    if (channels == 4) { //4 channels, RGBA32
        for (int index = 0; index < maxIndex; index += 4) {
            c.r = stbiData[index];
            c.g = stbiData[index + 1];
            c.b = stbiData[index + 2];
            c.a = stbiData[index + 3];

            //write data
            result->at(x, y) = c;
            x++;
            if (x == width) {
                x = 0;
                y++;
            }
        }
    } else if (channels == 3) { //3 channels, RGB24
        c.a = 255;
        for (int index = 0; index < maxIndex; index += 3) {
            c.r = stbiData[index];
            c.g = stbiData[index + 1];
            c.b = stbiData[index + 2];

            //write data
            result->at(x, y) = c;
            x++;
            if (x == width) {
                x = 0;
                y++;
            }
        }
    } else if (channels == 2) { //2 channels, grayscale and alpha
        for (int index = 0; index < maxIndex; index += 2) {
            c.r = stbiData[index];
            c.g = stbiData[index];
            c.b = stbiData[index];
            c.a = stbiData[index + 1];

            //write data
            result->at(x, y) = c;
            x++;
            if (x == width) {
                x = 0;
                y++;
            }
        }
    } else if (channels == 1) { //1 channel, grayscale
        c.a = 255;
        for (int index = 0; index < maxIndex; index++) {
            c.r = stbiData[index];
            c.g = stbiData[index];
            c.b = stbiData[index];

            //write data
            result->at(x, y) = c;
            x++;
            if (x == width) {
                x = 0;
                y++;
            }
        }
    } else { //either no channels or too many channels. Abort and return null
        delete result;
        result = NULL;
        cerr << "Couldn't read image into texture: " << channels << " channels provided, 1-4 expected." << endl;
    }

    stbi_image_free(stbiData);

    return result;
}