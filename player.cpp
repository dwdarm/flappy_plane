#ifndef PLAYER_h_
#include "player.h"

#include "libs/texturemap.h"

#define TILE_WIDTH  88
#define TILE_HEIGHT 73
#define TILE_COUNT  3
#define ROTATE      30
#define SPEED       2

const std::string PLANE_PATH[] = {
    "assets/Planes/planeGreen1.png",
    "assets/Planes/planeGreen2.png",
    "assets/Planes/planeGreen3.png"
};

const std::string PUFF_PATH[] = {
    "assets/puffSmall.png",
    "assets/puffLarge.png",
};

Player::Player(SDL_Renderer* renderer) {
    mRenderer = renderer;

    for (auto i : PLANE_PATH) {
        TextureMap::getInstance()->getTexture(mRenderer, i);
    }

    for (auto i : PUFF_PATH) {
        TextureMap::getInstance()->getTexture(mRenderer, i);
    }

    setTexture(TextureMap::getInstance()->getTexture(mRenderer, PLANE_PATH[0]).get());
    resize(TILE_WIDTH/2, TILE_HEIGHT/2);

    mPuff.setTexture(TextureMap::getInstance()->getTexture(mRenderer, PUFF_PATH[0]).get());

    reset();
    tick();
}

void Player::reset() {
    setPosition(100, 100);
}

void Player::tick() {
    static int dy = 0;
    setTexture(TextureMap::getInstance()->getTexture(mRenderer, PLANE_PATH[dy]).get());
    resize(TILE_WIDTH/2, TILE_HEIGHT/2);
    dy++;
    if (dy >= TILE_COUNT) {
        dy = 0;
    } 

    static int py = 0, updatePuff = 0;
    updatePuff++;
    if (updatePuff == 8) {
        mPuff.setTexture(TextureMap::getInstance()->getTexture(mRenderer, PUFF_PATH[py]).get());
        mPuff.setPosition(getX() - (getWidth() * (py+1)), getY());
        py++;
        if (py >= 2) {
            py = 0;
        } 

        updatePuff = 0;
    }
    
    if (mDir == UP) {
        move(0, -1 * mSpeed);
    } else if (mDir == DOWN) {
        move(0, mSpeed);
    } 
    
    if (getY() < 0) {
        setPosition(getX(), 0);
    }
}

void Player::up() {
    if (getRotate() > (-1 * ROTATE)) {
        rotate(-1 * ROTATE);
    }
    
    if (getRotate() == (-1 * ROTATE)) {
        mDir = UP;
    } else if (getRotate() == 0) {
        mDir = STRAIGHT;
    }
}

void Player::down() {
    if (getRotate() < ROTATE) {
        rotate(ROTATE);
    }
    
    if (getRotate() == ROTATE) {
        mDir = DOWN;
    } else if (getRotate() == 0) {
        mDir = STRAIGHT;
    }
}

void Player::gas() {
    mSpeed = 4;
}

void Player::release() {
    mSpeed = 2;
}

int Player::getDirection() {
    return mDir;
}

void Player::draw(SDL_Renderer* renderer) {
    Sprite::draw(renderer);
    mPuff.draw(renderer);
}

#endif