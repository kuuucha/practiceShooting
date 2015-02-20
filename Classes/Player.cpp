//
//  Player.cpp
//  ShootingGame
//
//  Created by 香織 on 2015/02/11.
//
//

#include "Player.h"

USING_NS_CC;

// ライフ
const int PLAYER_LIFE = 5;

Player::Player()
: _shootFlg(false)
, life(PLAYER_LIFE)
{
    
}

Player::~Player()
{
    
}

bool Player::init()
{
    return this->initWithFile("player_kari.png");
}

void Player::playerClash()
{
    this->setLife(this->getLife() - 1);
    
    log("ライフ %d", this->getLife());
}