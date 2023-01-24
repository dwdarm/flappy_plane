#ifndef GROUND_h_
#include "ground.h"

#include <fstream>
#include <cstdio>
#include <boost/polygon/polygon.hpp>

namespace gtl = boost::polygon;
using namespace boost::polygon::operators;

typedef gtl::polygon_data<float> Polygon;
typedef gtl::polygon_traits<Polygon>::point_type Point;

Ground::Ground(SDL_Renderer* renderer, const std::string &texturePath, const std::string &tilesetPath, int w, int h) {
    std::ifstream f(tilesetPath);
    mTileset = json::parse(f);
    
    mTexture.loadFromFile(renderer, texturePath);
    
    mScreenWidth = w;
    mScreenHeight = h;
    
    reset();
}

void Ground::reset() {
    mSprites.clear();
    
    for (int i = 0; i < 2; i++) {
        std::shared_ptr<Sprite> sprite(new Sprite());
        sprite->setTexture(&mTexture);
                
        if (i > 0) {
            sprite->setPosition(sprite->getWidth(), mScreenHeight - sprite->getHeight());
        } else {
            sprite->setPosition(0, mScreenHeight - sprite->getHeight());
        }
                
        mSprites.push_back(sprite);
    }
}

void Ground::tick() {
    for (std::shared_ptr<Sprite> sp : mSprites) {
        sp->move(-1 * mSpeed, 0);
        if ((sp->getX() + sp->getWidth()) < 0) {
            int state = rand() % 2;
            sp->setPosition(mScreenWidth, sp->getY());
        }
    }
}

void Ground::draw(SDL_Renderer* renderer) {
    for (std::shared_ptr<Sprite> sp : mSprites) {
        sp->draw(renderer);
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

bool _isCollide(Sprite &sprite, Sprite &ground, json &tileset) {
        json &objs = tileset["tiles"][0]["objectgroup"]["objects"][0];
        
        Polygon poly = _constructPolygon(
            objs["polygon"],
            objs["x"],
            objs["y"],
            ground.getX(),
            ground.getY()
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

bool Ground::checkCollide(Sprite &sprite) {
            
    if (sprite.getY() + sprite.getHeight() > mScreenHeight) {
        return true;
    }
            
    for (std::shared_ptr<Sprite> ground : mSprites) {
        if (_isCollide(sprite, *ground, mTileset)) {
            return true;
        }
    }
            
    return false;
}

void Ground::setSpeed(int speed) {
    mSpeed = speed;
}

#endif