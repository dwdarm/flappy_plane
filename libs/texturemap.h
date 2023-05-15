#ifndef TEXTUREMAP_h_
#define TEXTUREMAP_h_

#ifndef TEXTURE_h_
    #include "texture.h"
#endif

#include <string>
#include <map>
#include <memory>

class TextureMap {
    public:
        std::shared_ptr<Texture>& getTexture(SDL_Renderer* renderer, const std::string &path);
        static TextureMap* getInstance();
        
    private:
        TextureMap() {}
        static TextureMap *mInstance;
        std::map<std::string, std::shared_ptr<Texture>> mTextures;
};

#endif