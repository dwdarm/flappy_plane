#ifndef GROUND_h_
#define GROUND_h_

#include "libs/sprite.h"

#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Ground {
    public:
        Ground(SDL_Renderer* renderer, const std::string &tilesetPath, int w, int h);
        
        void reset();
        
        void tick();
        void draw(SDL_Renderer* renderer);
        
        bool checkCollide(Sprite &sprite);
        
        void setSpeed(int speed);
        
    private:
        SDL_Renderer* mRenderer;
        std::vector<std::shared_ptr<Sprite>> mSprites;
        json mTileset;
        int mScreenWidth = 0, mScreenHeight = 0;
        int mSpeed = 4;
};

#endif