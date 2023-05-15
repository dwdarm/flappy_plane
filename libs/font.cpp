#ifndef FONT_h_
#include "font.h"

#define DEFAULT_FONT_SIZE 16

bool Font::loadFromFile(const std::string &path) {
    mFont = TTF_OpenFont(path.c_str(), DEFAULT_FONT_SIZE);
    if (mFont == NULL) {
        printf("Unable to load font %s! SDL_ttf Error: %s\n", path.c_str(), SDL_GetError());
    }

    return mFont != NULL;
}

Font::~Font() {
    if (mFont != NULL) {
        TTF_CloseFont(mFont);
    }
}

#endif