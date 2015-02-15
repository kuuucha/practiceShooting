//
//  Enemy.h
//  ShootingGame
//
//  Created by 香織 on 2015/02/11.
//
//

#ifndef __ShootingGame__Enemy__
#define __ShootingGame__Enemy__

#include "cocos2d.h"

class Enemy :public cocos2d::Sprite
{
private:
    Enemy();
    virtual ~Enemy();
    bool init() override;
    
public:
    CREATE_FUNC(Enemy);
};

#endif /* defined(__ShootingGame__Enemy__) */
