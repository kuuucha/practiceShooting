//
//  Enemy.cpp
//  ShootingGame
//
//  Created by 香織 on 2015/02/11.
//
//

#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy()
{
    
}

Enemy::~Enemy()
{
    
}

bool Enemy::init()
{
   return this->initWithFile("enemy_kari.png");
}
