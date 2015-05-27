//
//  Saw.cpp
//  CoolRun
//
//  Created by ManYou on 15/2/27.
//
//

#include "Saw.h"
#include "Runner.h"
//#include "CoolRunScene.h"

Saw::Saw()
: MultipleCollideNode()
{
    
}
Saw::~Saw()
{
    
}
bool Saw::init()
{
    if (!MultipleCollideNode::init())
    {
        return false;
    }
    
    auto sp = Sprite::createWithSpriteFrameName("saw.png");
    auto csize = sp->getContentSize();
    this->setContentSize(csize);
    sp->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(sp);
    sp->runAction(RepeatForever::create(RotateBy::create(0.2, -60)));
    this->setCollideEffect(true);
    this->setGravityEffect(false);
    this->setCollideType(kCollideTypeSimple);
    this->setCollideRect(Rect(30, 30, csize.width-60, csize.height-60));
    
    this->addRect(Rect(46, 50, 40, 80)); //头部
    this->addRect(Rect(90, 50, 130, 100)); //尾部
    
    this->debugShow();
    
    this->setLocalZOrder(ZORDER_SAW);
    
    return true;
}

void Saw::trackCollideWithRunner(Runner* _runner)
{
    auto rect1 = PhysicHelp::countPhysicNodeRect(_runner);
    auto rect2 = PhysicHelp::countPhysicNodeRect(this);

    bool isCollide = _runner->isCollidedWithTrueBody(rect2);
    if (isCollide)
    {
        if (!_runner->isDad() && !_runner->isRebornING())
        {
            m_gameController->dead(_runner);
        }
        else
        {
            this->setDestoryed(true);
        }
    }

}