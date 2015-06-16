//
//  LogoScene.cpp
//  CoolRun
//
//  Created by ManYou on 15/6/12.
//
//

#include "LogoScene.h"
#include "MYScene.h"
#include "MenuScene.h"
#include "SceneHelp.h"

LogoLayer::LogoLayer()
: Layer()
{
}
LogoLayer::~LogoLayer()
{
    
}

Scene* LogoLayer::createScene()
{
    auto _scene = MYScene::create();
    auto _layer = LogoLayer::create();
    _scene->addChild(_layer);
    return _scene;
}

bool LogoLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(layer);
    
    auto sp = Sprite::create("launch.png");
    sp->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(sp);
    
    return true;
}


void LogoLayer::onEnter()
{
    Layer::onEnter();
    
    auto _delay = DelayTime::create(2.0f);
    auto _call = CallFunc::create(CC_CALLBACK_0(LogoLayer::showLogoEnd, this));
    this->runAction(Sequence::create(_delay, _call, NULL));
}

void LogoLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
 
}

void LogoLayer::showLogoEnd()
{
    auto scene = MenuLayer::createScene();
    SceneHelp::replaceScene(scene);
}