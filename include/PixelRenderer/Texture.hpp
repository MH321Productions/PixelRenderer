#pragma once

#include <vector>

#include <lunasvg.h>

#include "PixelRenderer/Loader.hpp"
#include "PixelRenderer/Renderer.hpp"

using rgb = unsigned char;

namespace PixelRenderer {

    class TextureManager;
    class VectorTexture;

    class Texture {
        friend class TextureManager;
        friend class VectorTexture;
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

    class VectorTexture {
        friend class TextureManager;
        private:
            std::unique_ptr<lunasvg::Document> doc;
            lunasvg::Bitmap bitmap;

            TextureManager* manager;
            Texture* target;
            LoadInfo info;

            VectorTexture(TextureManager* manager, const LoadInfo& info) : manager(manager), info(info), doc(nullptr) {}

            /**
             * Load the image
            */
            bool load();
        
        public:
            double width, height;
            ~VectorTexture();

            /**
             * Render the svg and store it in the texture for further use
             * @param width The desired width
             * @param height The desired height
             * @return The rendered texture (Do NOT delete it)
            */
            Texture* render(const int& width, const int& height);
    };

    class TextureManager {
        friend class Texture;
        private:
            std::vector<Texture*> loadedTextures;
            std::vector<VectorTexture*> loadedVectorTextures;
            bool blockRemoval = false;

            void removeTexture(Texture* texture);
            void removeTexture(VectorTexture* texture);
        
        public:
            TextureManager() {}
            ~TextureManager();

            Texture* getTexture(const LoadInfo& type);
            VectorTexture* getVectorTexture(const LoadInfo& type);
    };
}