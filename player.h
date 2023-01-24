#ifndef PLAYER_h_
#define PLAYER_h_

#include "libs/texture.h"
#include "libs/sprite.h"

enum {
    UP = 0,
    STRAIGHT,
    DOWN
} PLAYER_DIRECTION;

class Player : public Sprite {
    public:
        Player(SDL_Renderer* renderer, const std::string &texturePath);
        
        int getDirection();
        
        void reset();
        
        void tick();
        
        void up();
        void down();
        void gas();
        void release();
        
    private:
        Texture mTexture;
        int mDir = STRAIGHT;
        int mSpeed = 2;
};

#endif