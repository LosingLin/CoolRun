//
//  PopViewLayer.cpp
//  CoolRun
//
//  Created by ManYou on 15/2/13.
//
//

#include "PopViewLayer.h"

PopViewLayer::PopViewLayer()
: Layer()
{
    
}
PopViewLayer::~PopViewLayer()
{
    
}

bool PopViewLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto bg = LayerColor::create(Color4B(0, 0, 0, 150));
    this->addChild(bg);
    
    auto  touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(PopViewLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PopViewLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PopViewLayer::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(PopViewLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}


bool PopViewLayer::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    return true;
}
void PopViewLayer::onTouchMoved(Touch *touch, Event *unusedEvent)
{
    
}
void PopViewLayer::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    
}
void PopViewLayer::onTouchCancelled(Touch *touch, Event *unusedEvent)
{
    
}