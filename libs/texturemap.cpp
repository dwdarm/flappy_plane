#ifndef TEXTUREMAP_h_
#include "texturemap.h"

TextureMap* TextureMap::mInstance = NULL;

TextureMap* TextureMap::getInstance() {
    if (!TextureMap::mInstance) {
        TextureMap::mInstance = new TextureMap();
    }

    return TextureMap::mInstance;
}

std::shared_ptr<Texture>& TextureMap::getTexture(SDL_Renderer* renderer, const std::string &path) {
    auto it = mTextures.find(path);
    if (it == mTextures.end()) {
        std::shared_ptr<Texture> texture(new Texture());
        texture->loadFromFile(renderer, path);
        mTextures.insert(std::pair<std::string, std::shared_ptr<Texture>>(path, texture));
        return mTextures[path];
    } 

    return it->second;
}

#endif