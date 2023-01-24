#ifndef SCORE_h_
#include "score.h"

#include <string>
#include <cstdlib>

#define TILE_WIDTH  7
#define TILE_HEIGHT 10

#define MAX_NUM 9999
#define DIGITS 4

Score::Score(SDL_Renderer* renderer, const std::string &texturePath, int x, int y, int w, int h) {
    mTexture.loadFromFile(renderer, texturePath);
    mX = x;
    mY = y;
    mW = w;
    mH = h;
    
    for (int i = 0; i < DIGITS; i++) {
        std::shared_ptr<Sprite> sprite(new Sprite());
        sprite->setTexture(&mTexture);
        sprite->resize(mW, mH);
        sprite->setTextureRect(TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT);
        mSprites.push_back(sprite);
    }
}

void Score::draw(SDL_Renderer* renderer) {
    std::string num = std::to_string(mNum > MAX_NUM ? MAX_NUM : mNum);
   
    int i = 0;
    
    for (std::shared_ptr<Sprite> sprite : mSprites) {
        sprite->setTextureRect(atoi(std::string((char*)&num[i], 1).c_str()) * TILE_WIDTH, 0 , TILE_WIDTH, TILE_HEIGHT);
        sprite->setPosition(mX + (i * sprite->getWidth()), mY);
        sprite->draw(renderer);
        
        i++;
        
        if (i >= num.length()) {
            break;
        }
    }
}

void Score::display(int num) {
    mNum = num;
}

#endif