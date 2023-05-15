#ifndef BACKGROUND_h_
#include "background.h"

#include "libs/texturemap.h"

Background::Background(SDL_Renderer* renderer) {
    mRenderer = renderer;
    setTexture(TextureMap::getInstance()->getTexture(mRenderer, "assets/background.png").get());
}

void Background::tick() {
    static int dx = 0;
    setTextureRect(dx, 0 , getWidth(), getHeight());
    
    dx++;
}

#endif