#ifndef ROCKS_h_
#define ROCKS_h_

#include "libs/sprite.h"

#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Rocks {
    public:
        Rocks(SDL_Renderer* renderer, const std::string &tilesetPath, int w, int h);
        
        void reset();
        
        void tick();
        void draw(SDL_Renderer* renderer);
        
        void setScreen(int w, int h);
        bool checkCollide(Sprite &sprite, bool* starAcquired);
        
        void setSpeed(int speed);
        
    private:
        SDL_Renderer* mRenderer;
        std::vector<std::shared_ptr<Sprite>> mSprites, mStars;
        json mTileset;
        int mScreenWidth = 0, mScreenHeight = 0;
        int mSpeed = 4;
};

#endif