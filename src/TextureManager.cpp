#include <iostream>

#include "PixelRenderer/Texture.hpp"
#include "PixelRenderer/Renderer.hpp"

using namespace std;

Texture* TextureManager::getTexture(const LoadInfo& info) {
    for (Texture* t: loadedTextures) {
        if (t->info == info) return t; //Temporary
    }

    Texture* load = Texture::loadTexture(info, this);
    if (load) loadedTextures.push_back(load);

    return load;
}

TextureManager::~TextureManager() {
    blockRemoval = true; //The textures can't remove themselves

    for (Texture* t: loadedTextures) delete t;

    loadedTextures.clear();

    //cout << "Deleted TextureManager" << endl;
}

void TextureManager::removeTexture(Texture* texture) {
    if (!blockRemoval && texture != NULL) {
        for (vector<Texture*>::iterator it = loadedTextures.begin(); it != loadedTextures.end(); it++) {
            if ((*it) == texture) {
                loadedTextures.erase(it);
                break;
            }
        }
    }
}