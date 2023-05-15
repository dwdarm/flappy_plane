#ifndef FONT_h_
#define FONT_h_

#ifndef SDL_h_
    #include <SDL2/SDL.h>
#endif

#ifndef SDL_TTF_H_
    #include <SDL2/SDL_ttf.h>
#endif

#include <string>

class Font {
    public:
        Font() {}
        ~Font();
        
        bool loadFromFile(const std::string &path);
        
    private:
        TTF_Font *mFont = NULL;

    friend class Text;
};

#endif