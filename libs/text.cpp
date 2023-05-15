#ifndef TEXT_h_
#include "text.h"

void Text::setString(const std::string &str) {
    mStr = str;
}

void Text::setSize(int size) {
    mSize = size;
}

void Text::setColor(SDL_Color &color) {
    mColor = color;
}

void Text::setOutlineSize(int outlineSize) {
    mOutlineSize = outlineSize;
}

void Text::setOutlineColor(SDL_Color &color) {
    mOutlineColor = color;
}

void Text::setPosition(int x, int y) {
    mX = x;
    mY = y;
}

void Text::draw() {
    if (mOutlineSize <= 0) {
        TTF_SetFontSize(mFont->mFont, mSize);
        TTF_SetFontOutline(mFont->mFont, 0);
        SDL_Surface *text = TTF_RenderText_Blended(mFont->mFont, mStr.c_str(), mColor);

        SDL_Rect rect = { mX, mY, text->w, text->h}; 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, text);
        SDL_FreeSurface(text);

        SDL_RenderCopy(mRenderer, texture, NULL, &rect);
        SDL_DestroyTexture(texture);
    } else {
        TTF_SetFontSize(mFont->mFont, mSize);
        TTF_SetFontOutline(mFont->mFont, 0);
        SDL_Surface *fgText = TTF_RenderText_Blended(mFont->mFont, mStr.c_str(), mColor);

        TTF_SetFontOutline(mFont->mFont, mOutlineSize);
        SDL_Surface *bgText = TTF_RenderText_Blended(mFont->mFont, mStr.c_str(), mOutlineColor);

        SDL_Rect rect = { mOutlineSize, mOutlineSize, fgText->w, fgText->h}; 
        SDL_SetSurfaceBlendMode(fgText, SDL_BLENDMODE_BLEND); 
        SDL_BlitSurface(fgText, NULL, bgText, &rect); 
        SDL_FreeSurface(fgText); 

        SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, bgText);
        SDL_Rect textRect = { mX, mY, bgText->w, bgText->h };
        SDL_FreeSurface(bgText);

        SDL_RenderCopy(mRenderer, texture, NULL, &textRect);
        SDL_DestroyTexture(texture);
    }
}

#endif