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
    void update(float dt);
    
    /** プレイヤー弾を作成
     * @return 作成したプレイヤー弾
     */
    cocos2d::Sprite* addPlayerBullet();
    
    /** プレイヤー弾をマップから取り除く
     * @param 削除するプレイヤー弾
     * @return 削除されたか
     */
    bool removePlayerBullet(cocos2d::Sprite *playerBullet);
    
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(MainScene);
    CC_SYNTHESIZE(bool, _shootFlg, ShootFlg);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _playerBullets, PlayerBullets);
    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *, _player, Player);
    
};

#endif /* defined(__ShootingGame__MainScene__) */
