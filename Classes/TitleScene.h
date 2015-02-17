//
//  TitleScene.h
//  ShootingGame
//
//  Created by 香織 on 2015/02/15.
//
//

#ifndef __ShootingGame__TitleScene__
#define __ShootingGame__TitleScene__

#include "cocos2d.h"

class TitleScene :public cocos2d::Layer
{
private:
    TitleScene();
    virtual ~TitleScene();
    bool init() override;
    
public:
    static cocos2d::Scene* createScene();
    void onEnterTransitionDidFinish() override;
    CREATE_FUNC(TitleScene);
};

#endif /* defined(__ShootingGame__TitleScene__) */
