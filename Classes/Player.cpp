//
//  Player.cpp
//  ShootingGame
//
//  Created by 香織 on 2015/02/11.
//
//

#include "Player.h"

USING_NS_CC;

Player::Player()
: _shootFlg(false)
, _isClash(false)
{
    
}

Player::~Player()
{
    
}

bool Player::init()
{
    return this->initWithFile("player_kari.png");
}