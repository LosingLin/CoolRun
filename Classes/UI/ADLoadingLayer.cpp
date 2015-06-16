//
//  ADLoadingLayer.cpp
//  CoolRun
//
//  Created by ManYou on 15/6/14.
//
//

#include "ADLoadingLayer.h"
#include "MYMultiLanguageManager.h"

ADLoadingLayer::ADLoadingLayer()
: PopViewLayer()
{
    
}
ADLoadingLayer::~ADLoadingLayer()
{
    
}

bool ADLoadingLayer::init()
{
    if (!PopViewLayer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto _label = Label::createWithBMFont("NFTitle.fnt",
                                          MYMultiLanguageManager::getInstance()->getText("loading"));
    _label->setAnchorPoint(Vec2(0.5, 0.5));
    _label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(_label);
    
    return true;
}