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
    auto size = director->getWinSize();
    
    // 背景
    auto background = Sprite::create("background_kari.png");
    background->setPosition(Vec2(size.width / 2.0, size.height / 2.0));
    this->addChild(background);
    
    // プレイヤー
    auto player = Sprite::create("player_kari.png");
    this->setPlayer(player);
    _player->setPosition(Vec2(player->getContentSize().width / 2.0, size.height / 2.0));
    this->addChild(_player);

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        // タッチされたときの処理
        log("Touch at (%f, %f)", touch->getLocation().x, touch->getLocation().y);
        
        return true;
    };
    listener->onTouchMoved = [this, size](Touch* touch, Event* event) {
        // タッチ中に動いたとき
        // 前回とのタッチ位置との差をベクトルで取得
        Vec2 delta = touch->getDelta();
        
        // 現在の座標を取得
        Vec2 position = _player->getPosition();
        
        // 現在座標 + 移動量
        Vec2 newPosition = position + delta;
        
        newPosition = newPosition.getClampPoint(Vec2(0, 0), Vec2(size.width, size.height));
        
        _player->setPosition(newPosition);
    };
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}