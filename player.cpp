#ifndef PLAYER_h_
#include "player.h"

#define TILE_WIDTH  88
#define TILE_HEIGHT 73
#define TILE_COUNT  3
#define ROTATE      30
#define SPEED       2

Player::Player(SDL_Renderer* renderer, const std::string &texturePath) {
    mTexture.loadFromFile(renderer, texturePath);
    setTexture(&mTexture);
    resize(TILE_WIDTH/2, TILE_HEIGHT/2);
    reset();
    tick();
}

void Player::reset() {
    setPosition(100, 100);
}

void Player::tick() {
    static int dy = 0;
    setTextureRect(0, dy * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
    
    dy++;
    
    if (dy >= TILE_COUNT) {
        dy = 0;
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

#endif