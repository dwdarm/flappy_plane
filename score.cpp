#ifndef SCORE_h_
#include "score.h"

#include <string>
#include <cstdlib>

#define TTF_PATH "assets/Fonts/kenvector_future.ttf"
#define FONT_SIZE 32
#define OUTLINE_SIZE 2

Score::Score(SDL_Renderer* renderer, int x, int y) {
    mFont = new Font();
    mFont->loadFromFile(TTF_PATH);

    mText = new Text(renderer, mFont);
    mText->setPosition(x, y);
    mText->setSize(FONT_SIZE);
    mText->setOutlineSize(OUTLINE_SIZE);
}

void Score::draw() {
    mText->setString(std::to_string(mNum));
    mText->draw();
}

void Score::display(int num) {
    mNum = num;
}

#endif