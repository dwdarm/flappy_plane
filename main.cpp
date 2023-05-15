#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <time.h>
#include <cstdlib>

#include "background.h"
#include "rocks.h"
#include "ground.h"
#include "player.h"
#include "score.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

typedef struct {
    SDL_Renderer* renderer;
    Background bg;
    Rocks      rocks;
    Ground     ground;
    Player     pl;
    Score      score;
    int        currentScore;
    bool       pause;
    bool       reset;
} Data;

Uint32 callback(Uint32 interval, void* param) {
    Data* data = reinterpret_cast<Data*>(param);
    bool star = false;
    
    if (data->pause == false) {
        data->bg.tick();
        data->rocks.tick();
        data->ground.tick();
        data->pl.tick();
        
        if (data->rocks.checkCollide(data->pl, &star) || data->ground.checkCollide(data->pl)) {
            data->pause = true;
        }
        
        if (star == true) {
            data->currentScore += 1;
            data->score.display(data->currentScore);
        }
    }
    
    if (data->reset == true) {
        data->rocks.reset();
        data->ground.reset();
        data->pl.reset();
        data->pause = false;
        data->reset = false;
    }
    
    return interval;
};

int main( int argc, char* args[] )
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    } 

    if(TTF_Init() < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    
    window = SDL_CreateWindow("Flappy Plane", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return -1;
    }
    
    srand(time(0));
    
    Data data = {
        renderer,
        Background(renderer),
        Rocks(renderer, "assets/rock.json", SCREEN_WIDTH, SCREEN_HEIGHT),
        Ground(renderer, "assets/ground.json", SCREEN_WIDTH, SCREEN_HEIGHT),
        Player(renderer),
        Score(renderer, (SCREEN_WIDTH / 2), 24),
        0,
        false,
        false
    };
    
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    SDL_TimerID timerID = SDL_AddTimer(17, callback, reinterpret_cast<void*>(&data));
    
    bool quit = false;
    SDL_Event e;
    
    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            } else if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_UP:
                        data.pl.up();
                        break;
                    case SDLK_DOWN:
                        data.pl.down();
                        break;
                    case SDLK_r:
                        data.reset = true;
                        break;
                    case SDLK_SPACE:
                        data.pl.gas();
                        if (data.pl.getDirection() == STRAIGHT) {
                            data.rocks.setSpeed(8);
                            data.ground.setSpeed(8);
                        } else {
                            data.rocks.setSpeed(6);
                            data.ground.setSpeed(6);
                        }
                        break;
                    default:
                        break;
                }
            } else if(e.type == SDL_KEYUP) {
                switch(e.key.keysym.sym) {
                    case SDLK_SPACE:
                        data.pl.release();
                        data.rocks.setSpeed(4);
                        data.ground.setSpeed(4);
                        break;
                    default:
                        break;
                }
            }
        }

        SDL_RenderClear(renderer);
        data.bg.draw(renderer);
        data.rocks.draw(renderer);
        data.ground.draw(renderer);
        data.pl.draw(renderer);
        data.score.draw();
        SDL_RenderPresent(renderer);
    }
    
    SDL_RemoveTimer(timerID);

    return 0;
}