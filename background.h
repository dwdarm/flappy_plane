#ifndef BACKGROUND_h_
#define BACKGROUND_h_

#include "libs/texture.h"
#include "libs/sprite.h"

class Background : public Sprite {
    public:
        Background(SDL_Renderer* renderer, const std::string &texturePath);
        
        void tick();
        
    private:
        Texture mTexture;
};

#endif