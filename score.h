#ifndef SCORE_h_
#define SCORE_h_

#include "libs/texture.h"
#include "libs/sprite.h"

#include <vector>
#include <memory>

class Score {
    public:
        Score(SDL_Renderer* renderer, const std::string &texturePath, int x, int y, int w, int h);
        
        void display(int num);
        void draw(SDL_Renderer* renderer);
        
    private:
        Texture mTexture;
        std::vector<std::shared_ptr<Sprite>> mSprites;
        int mX, mY, mW, mH;
        int mNum = 0;
};

#endif