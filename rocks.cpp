#ifndef ROCKS_h_
#include "rocks.h"

#include "libs/texturemap.h"

#include <fstream>
#include <cstdio>
#include <boost/polygon/polygon.hpp>

#define TILE_WIDTH  108
#define TILE_HEIGHT 239

#define STAR_WIDTH  39
#define STAR_HEIGHT 38

const std::string ROCK_PATH[] = {
    "assets/rockGrass.png",
    "assets/rockGrassDown.png",
};

const std::string STAR_PATH[] = {
    "assets/starBronze.png",
    "assets/starSilver.png",
    "assets/starGold.png"
};

namespace gtl = boost::polygon;
using namespace boost::polygon::operators;

typedef gtl::polygon_data<float> Polygon;
typedef gtl::polygon_traits<Polygon>::point_type Point;

typedef struct {
    bool visible;
} StarState;

static void _createRocks(SDL_Renderer *renderer, std::vector<std::shared_ptr<Sprite>> &sprites, std::vector<std::shared_ptr<Sprite>> &stars, int w, int h) {
            
    for (int i = 0; i < 4; i++) {
        int state = rand() % 2;
        std::shared_ptr<Sprite> sprite(new Sprite());
        std::shared_ptr<Sprite> star(new Sprite());
        int posY = state == 0 ?  h - TILE_HEIGHT : 0;
        
        sprite->setTexture(TextureMap::getInstance()->getTexture(renderer, ROCK_PATH[state]).get());
        sprite->resize(TILE_WIDTH, TILE_HEIGHT);
        //sprite->setTextureRect(0, state == 0 ? TILE_HEIGHT : 0 , TILE_WIDTH, TILE_HEIGHT);
        
        star->setTexture(TextureMap::getInstance()->getTexture(renderer, STAR_PATH[2]).get());
        star->resize(STAR_WIDTH, STAR_HEIGHT);
        //star->setTextureRect(0, 2 * TILE_HEIGHT, STAR_WIDTH, STAR_HEIGHT);
        StarState* starState = new StarState();
        starState->visible = rand() % 2 == 1;
        star->data = (void*)(starState);
        
        int* data = new int(state);
        sprite->data = (void*)(data);
                
        if (i > 0) {
            sprite->setPosition(sprites[i - 1]->getX() + (2 * sprites[i - 1]->getWidth()), posY);
        } else {
            sprite->setPosition(w, posY);
        }
        
        star->setPosition(sprite->getX() + (sprite->getWidth()/2), state == 0 ? (sprite->getY() - star->getHeight()) - star->getHeight() : sprite->getHeight() + star->getHeight());
                
        sprites.push_back(sprite);
        stars.push_back(star);
    }
}

Rocks::Rocks(SDL_Renderer* renderer, const std::string &tilesetPath, int w, int h) {
    mRenderer = renderer;

    std::ifstream f(tilesetPath);
    mTileset = json::parse(f);
    
    for(auto i : ROCK_PATH) {
        TextureMap::getInstance()->getTexture(mRenderer, i);
    }

    for(auto i : STAR_PATH) {
        TextureMap::getInstance()->getTexture(mRenderer, i);
    }
    
    mScreenWidth = w;
    mScreenHeight = h;
    
    reset();
}

void Rocks::reset() {
    mSprites.clear();
    mStars.clear();
    _createRocks(mRenderer, mSprites, mStars, mScreenWidth, mScreenHeight);
}

void Rocks::setScreen(int w, int h) {
    mScreenWidth = w;
    mScreenHeight = h;
}

void Rocks::tick() {
    for (int i = 0; i < mSprites.size(); i++) {
        Sprite *sp = mSprites[i].get();
        Sprite *st = mStars[i].get();
        
        sp->move(-1 * mSpeed, 0);
        st->move(-1 * mSpeed, 0);
        
        if ((sp->getX() + sp->getWidth()) < 0) {
            int state = rand() % 2;
            //sp->setTextureRect(0, state == 0 ? TILE_HEIGHT : 0 , TILE_WIDTH, TILE_HEIGHT);
            sp->setTexture(TextureMap::getInstance()->getTexture(mRenderer, ROCK_PATH[state]).get());
            sp->resize(TILE_WIDTH, TILE_HEIGHT);
            *(int*)sp->data = state; 
            sp->setPosition(mScreenWidth, state == 0 ? mScreenHeight - TILE_HEIGHT : 0);
            
            StarState* sts = (StarState*)st->data;
            sts->visible = rand() % 2 == 1;
            st->setPosition(sp->getX() + (sp->getWidth()/2), state == 0 ? (sp->getY() - st->getHeight()) - (st->getHeight()) : sp->getHeight() + (st->getHeight()));
        }
       
    }
}

void Rocks::draw(SDL_Renderer* renderer) {
    for (std::shared_ptr<Sprite> sp : mSprites) {
        sp->draw(renderer);
    }
    
    for (std::shared_ptr<Sprite> sp : mStars) {
        StarState* st = (StarState*)sp->data;
        if (st->visible == true) {
            sp->draw(renderer);
        }
    }
}

static Polygon _constructPolygon(json &obj, float startX, float startY, float offsetX, float offsetY) {
    std::vector<Point> points;
    Polygon poly;
            
    for (json::iterator it = obj.begin(); it != obj.end(); ++it) {
        float x = it.value()["x"], y = it.value()["y"];
            points.push_back(gtl::construct<Point>(
                x + startX + offsetX, 
                y + startY + offsetY
        ));
    }
            
    gtl::set_points(poly, &points[0], &points[0] + points.size());
            
    return poly;
}

bool _isCollide(Sprite &sprite, Sprite &rock, json &tileset, int h) {
        int state = *(int*)rock.data;
        json &objs = tileset["tiles"][state == 0 ? 1 : 0]["objectgroup"]["objects"][0];
        
        Polygon poly = _constructPolygon(
            objs["polygon"],
            objs["x"],
            objs["y"],
            rock.getX(),
            state == 0 ? h - rock.getHeight() : 0
        );
            
        return 
            gtl::contains(poly, gtl::construct<Point>(
                sprite.getX() + sprite.getWidth(), 
                sprite.getY()
            )) || 
            gtl::contains(poly, gtl::construct<Point>(
                sprite.getX() + sprite.getWidth(), 
                sprite.getY() + sprite.getHeight()
            ));
}

bool Rocks::checkCollide(Sprite &sprite, bool* starAcquired) {
    
    if (starAcquired != NULL) {
        *starAcquired = false;
    }
    
    int spriteRight = sprite.getX() + sprite.getWidth();
    int spriteBottom = sprite.getY() + sprite.getHeight();
    
    for (std::shared_ptr<Sprite> star : mStars) {
       
        if ((sprite.getX() > star->getX() &&
            sprite.getX() < (star->getX() + star->getWidth()) &&
            sprite.getY() > star->getY() &&
            sprite.getY() < (star->getY() + star->getHeight())) ||
            (spriteRight > star->getX() &&
            spriteRight < (star->getX() + star->getWidth()) &&
            spriteBottom > star->getY() &&
            spriteBottom < (star->getY() + star->getHeight()))
        ) {
            StarState* st = (StarState*)star->data;
            if (st->visible == true) {
                if (starAcquired != NULL) {
                    *starAcquired = true;
                }
                st->visible = false;
            }
            
            break;
        }
    }
             
    for (std::shared_ptr<Sprite> rock : mSprites) {
        if (_isCollide(sprite, *rock, mTileset, mScreenHeight)) {
            return true;
        }
    }
            
    return false;
}

void Rocks::setSpeed(int speed) {
    mSpeed = speed;
}

#endif