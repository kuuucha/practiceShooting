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
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

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
    Bullet *addPlayerBullet();
    
    /** プレイヤー弾をマップから取り除く
     * @param 削除するプレイヤー弾
     * @return 削除されたか
     */
    bool removePlayerBullet(Bullet *playerBullet);
    
    /** min ~ maxの乱数をfloatで返す
     * @param min
     * @param max
     * @return min <= n < max
     */
    float generateRandom(float min, float max);
    
    /** 敵を作成
     * @return 作成した敵
     */
    Enemy *addEnemy();
    
    /** 敵をマップから取り除く
     * @param 削除する敵
     * @return 削除されたか
     */
    bool removeEnemy(Enemy *enemy);
    
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(MainScene);
    CC_SYNTHESIZE(cocos2d::Vector<Bullet *>, _playerBullets, PlayerBullets);
    CC_SYNTHESIZE(std::mt19937, _engine, Engine);
    CC_SYNTHESIZE(cocos2d::Vector<Enemy *>, _enemys, Enemys);
    CC_SYNTHESIZE_RETAIN(Player *, _player, Player);
    
};

#endif /* defined(__ShootingGame__MainScene__) */
