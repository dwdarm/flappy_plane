#ifndef SCORE_h_
#define SCORE_h_

#include <SDL2/SDL.h>
#include <vector>
#include <memory>

#include "libs/text.h"

class Score {
    public:
        Score(SDL_Renderer* renderer, int x, int y);
        
        void display(int num);
        void draw();
        
    private:
        Font *mFont;
        Text *mText;
        int mNum = 0;
};

#endif