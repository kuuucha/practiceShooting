//
//  Bullet.h
//  ShootingGame
//
//  Created by 香織 on 2015/02/11.
//
//

#ifndef __ShootingGame__Bullet__
#define __ShootingGame__Bullet__

#include "cocos2d.h"

class Bullet :public cocos2d::Sprite
{
private:
    Bullet();
    virtual ~Bullet();
    bool init() override;
    
public:
    CREATE_FUNC(Bullet);
};

#endif /* defined(__ShootingGame__Bullet__) */
