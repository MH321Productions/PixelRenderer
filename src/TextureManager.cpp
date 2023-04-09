#include <iostream>

#include "PixelRenderer/Texture.hpp"
#include "PixelRenderer/Renderer.hpp"

using namespace std;

namespace PixelRenderer {
    
    Texture* TextureManager::getTexture(const LoadInfo& info) {
        for (Texture* t: loadedTextures) {
            if (t->info == info) return t; //Temporary
        }

        Texture* load = Texture::loadTexture(info, this);
        if (load) loadedTextures.push_back(load);

        return load;
    }

    VectorTexture* TextureManager::getVectorTexture(const LoadInfo& info) {
        for (VectorTexture* t: loadedVectorTextures) {
            if (t->info == info) return t; //Temporary
        }

        VectorTexture* load = new VectorTexture(this, info);
        if (load->load()) loadedVectorTextures.push_back(load);
        else {
            delete load;
            load = NULL;
        }

        return load;
    }

    TextureManager::~TextureManager() {
        blockRemoval = true; //The textures can't remove themselves

        for (Texture* t: loadedTextures) delete t;
        for (VectorTexture* t: loadedVectorTextures) delete t;

        loadedTextures.clear();
        loadedVectorTextures.clear();

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

    void TextureManager::removeTexture(VectorTexture* texture) {
        if (!blockRemoval && texture != NULL) {
            for (vector<VectorTexture*>::iterator it = loadedVectorTextures.begin(); it != loadedVectorTextures.end(); it++) {
                if ((*it) == texture) {
                    loadedVectorTextures.erase(it);
                    break;
                }
            }
        }
    }
}