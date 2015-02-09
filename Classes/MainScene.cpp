//
//  MainScene.cpp
//  ShootingGame
//
//  Created by 香織 on 2015/02/08.
//
//

#include "MainScene.h"

USING_NS_CC;

MainScene::MainScene()
: _player(NULL)
, _shootFlg(false)
{
    
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
    auto player = Sprite::create("player_kari.png");
    this->setPlayer(player);
    _player->setPosition(Vec2(winSize.width /2.0, player->getContentSize().height / 2.0));
    this->addChild(_player);

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        // タッチされたときの処理
        log("Touch at (%f, %f)", touch->getLocation().x, touch->getLocation().y);
        
        // 垂れ流しフラグ
        this->setShootFlg(true);

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
        this->setShootFlg(false);
    };
    
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    // updateを毎フレーム実行
    this->scheduleUpdate();
    
    return true;
}

void MainScene::update(float dt)
{
    // タッチ中
    if (this->getShootFlg()) {
        this->addPlayerBullet();
    }
}

Sprite* MainScene::addPlayerBullet()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // 弾を作成
    auto playerBullet = Sprite::create("tama_kari.png");
    // 位置をセット
    auto playerPosition = _player->getPosition();
    playerBullet->setPosition(Vec2(playerPosition.x, playerPosition.y));
    
    this->addChild(playerBullet);
    _playerBullets.pushBack(playerBullet);

    // プレイヤー弾を飛ばす
    auto shoot = MoveTo::create(3, Vec2(playerBullet->getPosition().x, visibleSize.height));
    
    auto remove = CallFuncN::create([this](Node *node) {
        // NodeをSpriteにダウンキャスト
        auto sprite = dynamic_cast<Sprite *>(node);
        
        // remove
        this->removePlayerBullet(sprite);
    });
    
    auto sequence = Sequence::create(shoot, remove, NULL);
    playerBullet->runAction(sequence);
    
    return playerBullet;
}

bool MainScene::removePlayerBullet(cocos2d::Sprite *playerBullet)
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
