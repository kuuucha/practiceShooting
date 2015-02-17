//
//  TitleScene.cpp
//  ShootingGame
//
//  Created by 香織 on 2015/02/15.
//
//

#include "TitleScene.h"
#include "MainScene.h"

USING_NS_CC;

TitleScene::TitleScene()
{
    
}

TitleScene::~TitleScene()
{
    
}

Scene* TitleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TitleScene::create();

    scene->addChild(layer);
    
    return scene;
}

bool TitleScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto director = Director::getInstance();
    auto winsize = director->getWinSize();
    
    // 背景
    auto background = Sprite::create("background_kari.png");
    background->setPosition(Vec2(winsize.width / 2.0, winsize.height / 2.0));
    this->addChild(background);
    
    // ロゴ
    auto logo = Label::createWithSystemFont("シューティングゲーム", "VL PGothic", 30);
    logo->setPosition(Vec2(winsize.width / 2.0, winsize.height - 40));
    logo->enableShadow();
    logo->enableOutline(Color4B::RED, 3);
    this->addChild(logo);
    
    // スタートボタン
    auto startButton = Label::createWithSystemFont("タップでスタート！", "VL PGothic", 30);
    startButton->setPosition(Vec2(winsize.width / 2.0, winsize.height / 2.0));
    
    // 点滅
    auto blink = Sequence::create(FadeTo::create(0.5, 127),
                                  FadeTo::create(0.5, 255),
                                  NULL);
    startButton->runAction(RepeatForever::create(blink));
    this->addChild(startButton);
    
    // 画面をタッチしたとき
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        
        this->getEventDispatcher()->removeAllEventListeners();
        // 0.5秒後にcallFunc
        auto delay = DelayTime::create(0.5);
        // ゲームを始めるアクション
        auto startGame = CallFunc::create([] {
            auto scene = MainScene::createScene();
            auto transition = TransitionTurnOffTiles::create(0.5, scene);
            Director::getInstance()->replaceScene(transition);
        });
        
        this->runAction(Sequence::create(delay, startGame, NULL));
        return true;
    };
    
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void TitleScene::onEnterTransitionDidFinish()
{
    
}