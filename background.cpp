#ifndef BACKGROUND_h_
#include "background.h"

Background::Background(SDL_Renderer* renderer, const std::string &texturePath) {
    mTexture.loadFromFile(renderer, texturePath);
    setTexture(&mTexture);
}

void Background::tick() {
    static int dx = 0;
    setTextureRect(dx, 0 , getWidth(), getHeight());
    
    dx++;
}

#endif