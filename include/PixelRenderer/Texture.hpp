#pragma once

#include <vector>

#include "Loader.hpp"

using rgb = unsigned char;

class Color;

class TextureManager;

class Texture {
    friend class TextureManager;
    private:
        std::vector<Color> data;
        TextureManager* manager;
        LoadInfo info;
        
        Texture(const int& width, const int& height, const int& channel, TextureManager* manager, const LoadInfo& info);

        static Texture* loadTexture(const LoadInfo& info, TextureManager* manager);
    
    public:
        int width, height, channel;
        Texture() : data({}), width(0), height(0), channel(0) {}
        ~Texture();

        const std::vector<Color>& getData() const;

        Color& at(const int& x, const int& y);
        inline bool isOutside(const int& x, const int& y) const {return x < 0 || y < 0 || x >= width || y >= height;}

};

class TextureManager {
    friend class Texture;
    private:
        std::vector<Texture*> loadedTextures;
        bool blockRemoval = false;

        void removeTexture(Texture* texture);
    
    public:
        TextureManager() {}
        ~TextureManager();

        Texture* getTexture(const LoadInfo& type);
};