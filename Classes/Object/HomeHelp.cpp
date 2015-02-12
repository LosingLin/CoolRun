//
//  HomeHelp.cpp
//  CoolRun
//
//  Created by ManYou on 14/11/6.
//
//

#include "HomeHelp.h"
#include "ActionHelp.h"


HomeHelp::HomeHelp()
: Animal()
{
}
HomeHelp::~HomeHelp()
{
}
bool HomeHelp::init()
{
    if (!Animal::init())
    {
        return false;
    }
    
    auto help = Sprite::createWithSpriteFrameName("help_01.png");
    auto csize = help->getContentSize();
    this->setContentSize(csize);
    help->setAnchorPoint(Vec2::ZERO);
    this->addChild(help);
    
    this->setCollideRect(Rect(0, 0, 362, 184));
//    this->setCollideEffect(true);
//    this->setGravityEffect(true);
    
    auto action01 = ActionHelp::createFrameAction("help_%02d.png", 1, 3, 0.3, true);
    help->runAction(action01);
    
    this->debugShow();
    
    return true;
}

void HomeHelp::CollideTrackListener_CollideOnce(CollideDirection direction, PhysicNode *node)
{
    Animal::CollideTrackListener_CollideOnce(direction, node);
}
void HomeHelp::CollideTrackListener_CollideAll(CollideDirection direction)
{
    Animal::CollideTrackListener_CollideAll(direction);
}