//
//  MainScene.h
//  ShootingGame
//
//  Created by 香織 on 2015/02/08.
//
//

#ifndef __ShootingGame__MainScene__
#define __ShootingGame__MainScene__

#include "cocos2d.h"

class MainScene :public cocos2d::Layer
{
protected:
    MainScene();
    virtual ~MainScene();
    bool init() override;
    
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(MainScene);
    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *, _player, Player);
    
};

#endif /* defined(__ShootingGame__MainScene__) */
