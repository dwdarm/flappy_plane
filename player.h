#ifndef PLAYER_h_
#define PLAYER_h_

#include "libs/texture.h"
#include "libs/sprite.h"
#include "libs/texturemap.h"

enum {
    UP = 0,
    STRAIGHT,
    DOWN
} PLAYER_DIRECTION;

class Player : public Sprite {
    public:
        Player(SDL_Renderer* renderer);
        
        int getDirection();
        
        void reset();
        
        void tick();
        
        void up();
        void down();
        void gas();
        void release();

        void draw(SDL_Renderer* renderer);
        
    private:
        SDL_Renderer* mRenderer;
        Sprite mPuff;
        int mDir = STRAIGHT;
        int mSpeed = 2;
};

#endif