//
//  Player.h
//  ShootingGame
//
//  Created by 香織 on 2015/02/11.
//
//

#ifndef __ShootingGame__Player__
#define __ShootingGame__Player__

#include "cocos2d.h"

class Player :public cocos2d::Sprite
{
protected:
    Player();
    virtual ~Player();
    bool init() override;
    
public:
    CC_SYNTHESIZE(bool, _shootFlg, ShootFlg);
    CC_SYNTHESIZE(bool, _isClash, IsClash);
    CC_SYNTHESIZE(int, life, Life);
    CREATE_FUNC(Player);
    
    /** クラッシュ
     */
    void playerClash();

};

#endif /* defined(__ShootingGame__Player__) */
