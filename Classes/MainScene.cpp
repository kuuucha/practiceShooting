//
//  MainScene.cpp
//  ShootingGame
//
//  Created by 香織 on 2015/02/08.
//
//

#include <random>
#include "MainScene.h"

USING_NS_CC;

// 敵出現率
const float ENEMY_PROBABILITY_RATE = 0.02;

MainScene::MainScene()
: _player(NULL)
{
    // 乱数の初期化
    std::random_device rdev;
    _engine.seed(rdev());
}

MainScene::~MainScene()
{
    CC_SAFE_RELEASE_NULL(_player);
}

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // ディレクター
    auto director = Director::getInstance();
    // 画面サイズ
    auto winSize = director->getWinSize();
    
    // 背景
    auto background = Sprite::create("background_kari.png");
    background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(background);
    
    // プレイヤー
    Player* player = Player::create();
    player->setPosition(Vec2(winSize.width / 2.0, player->getContentSize().height / 2.0));
    this->setPlayer(player);
    this->addChild(_player);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        // タッチされたときの処理
        log("Touch at (%f, %f)", touch->getLocation().x, touch->getLocation().y);
        
        // 垂れ流しフラグ
        _player->setShootFlg(true);

        return true;
    };
    listener->onTouchMoved = [this, winSize](Touch* touch, Event* event) {
        // タッチ中
        // 前回とのタッチ位置との差をベクトルで取得
        Vec2 delta = touch->getDelta();
        
        // 現在の座標を取得
        Vec2 position = _player->getPosition();
        
        // 現在座標 + 移動量
        Vec2 newPosition = position + delta;
        
        newPosition = newPosition.getClampPoint(Vec2(0, 0), Vec2(winSize.width, winSize.height));
        
        _player->setPosition(newPosition);
    };
    listener->onTouchEnded = [this] (Touch* touch, Event* event) {
        // タッチが終わったとき
        _player->setShootFlg(false);
    };
    
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    // updateを毎フレーム実行
    this->scheduleUpdate();

    return true;
}

void MainScene::update(float dt)
{
    // タッチ中
    if (_player->getShootFlg()) {
        this->addPlayerBullet();
    }

    float r = this->generateRandom(0, 1);
    if (r <= ENEMY_PROBABILITY_RATE) {
        // 敵出現
        this->addEnemy();
    }

    // 敵とのあたり判定
    for (auto& enemy : _enemys)
    {
        if (!enemy->getParent()){
            continue;
        }
        
        // 矩形
        Rect enemyRect = enemy->getBoundingBox();
        Rect playerRect = _player->getBoundingBox();
        
        // 敵とプレイヤーが衝突した場合
        if (playerRect.intersectsRect(enemyRect))
        {
            // 敵をマップから削除
            this->removeEnemy(enemy);
            
            // プレイヤーをクラッシュ
            _player->setIsClash(true);
        }
        
        // 敵とプレイヤー弾が衝突した場合
        for (auto& bullet : _playerBullets)
        {
            Rect bulletRect = bullet->getBoundingBox();
            
            if (enemyRect.intersectsRect(bulletRect))
            {
                // 敵をマップから削除
                this->removeEnemy(enemy);
                
                // プレイヤー弾をマップから削除
                this->removePlayerBullet(bullet);
            }
        }
    }

    // プレイヤーがクラッシュしている場合
    if (_player->getIsClash())
    {
        _player->setIsClash(false);
    }
}

Bullet *MainScene::addPlayerBullet()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // 弾を作成
    auto playerBullet = Bullet::create();
    // 位置をセット
    auto playerPosition = _player->getPosition();
    playerBullet->setPosition(Vec2(playerPosition.x, playerPosition.y));
    
    this->addChild(playerBullet);
    _playerBullets.pushBack(playerBullet);

    // プレイヤー弾を飛ばす
    auto shoot = MoveTo::create(3, Vec2(playerBullet->getPosition().x, visibleSize.height));
    
    auto remove = CallFuncN::create([this](Node *node) {
        // NodeをSpriteにダウンキャスト
        auto sprite = dynamic_cast<Bullet *>(node);
        
        // remove
        this->removePlayerBullet(sprite);
    });
    
    auto sequence = Sequence::create(shoot, remove, NULL);
    playerBullet->runAction(sequence);
    
    return playerBullet;
}

bool MainScene::removePlayerBullet(Bullet *playerBullet)
{
    if (_playerBullets.contains(playerBullet)) {
        // 親ノードから削除
        playerBullet->removeFromParent();
        // _playerBullets配列から削除
        _playerBullets.eraseObject(playerBullet);
        
        return true;
    }

    return false;
}

float MainScene::generateRandom(float min, float max)
{
    std::uniform_real_distribution<float> dest(min, max);
    return dest(_engine);
}

Enemy *MainScene::addEnemy()
{
    auto winSize = Director::getInstance()->getWinSize();
    // 敵を作成
    auto enemy = Enemy::create();

    // 出現位置
    auto enemySize = enemy->getContentSize();
    float enemyXPos = this->generateRandom(enemySize.width / 2.0, winSize.width - enemySize.width / 2.0);
    float enemyYPos = this->generateRandom(winSize.height / 2.0, winSize.height - enemySize.height / 2.0);
    enemy->setPosition(Vec2(enemyXPos, enemyYPos));

    this->addChild(enemy);
    _enemys.pushBack(enemy);

    return enemy;
}

bool MainScene::removeEnemy(Enemy *enemy)
{
    if (_enemys.contains(enemy))
    {
        // 親ノードから削除
        enemy->removeFromParent();
        // _enemysから削除
        _enemys.eraseObject(enemy);
        
        return true;
    }
    
    return false;
}
