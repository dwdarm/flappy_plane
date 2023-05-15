#ifndef BACKGROUND_h_
#define BACKGROUND_h_

#include "libs/sprite.h"

class Background : public Sprite {
    public:
        Background(SDL_Renderer* renderer);
        
        void tick();
        
    private:
        SDL_Renderer* mRenderer;
};

#endif