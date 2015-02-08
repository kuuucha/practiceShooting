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
{
    
}

MainScene::~MainScene()
{
    
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
    
    return true;
}