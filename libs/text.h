#ifndef TEXT_h_
#define TEXT_h_

#ifndef SDL_h_
    #include <SDL2/SDL.h>
#endif

#ifndef SDL_TTF_H_
    #include <SDL2/SDL_ttf.h>
#endif

#ifndef FONT_h_
    #include "font.h"
#endif

#include <string>

#define DEFAULT_TEXT_SIZE 16
#define DEFAULT_OUTLINE_SIZE 0

class Text {
    public:
        Text(SDL_Renderer *renderer, Font *font) : mRenderer(renderer), mFont(font) {}
        void setString(const std::string &str);

        void setSize(int size);
        void setColor(SDL_Color &color);

        void setOutlineSize(int outlineSize);
        void setOutlineColor(SDL_Color &color);

        void setPosition(int x, int y);

        void draw();
        
    private:
        SDL_Renderer *mRenderer;
        int mX = 0, mY = 0;
        Font *mFont;
        std::string mStr;
        int mSize = DEFAULT_TEXT_SIZE;
        SDL_Color mColor = { 0xFF, 0xFF, 0xFF, 0 };
        int mOutlineSize = DEFAULT_OUTLINE_SIZE;
        SDL_Color mOutlineColor = { 0x00, 0x00, 0x00, 0 }; 
};

#endif