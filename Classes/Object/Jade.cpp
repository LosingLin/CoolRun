//
//  Jade.cpp
//  CoolRun
//
//  Created by ManYou on 15/7/1.
//
//

#include "Jade.h"


Jade::Jade()
: Treasure()
, m_jadeNum(0)
{
    
}
Jade::~Jade()
{
    
}
bool Jade::init()
{
    if (!Treasure::init())
    {
        return false;
    }
    
    m_sp = Sprite::createWithSpriteFrameName("jade.png");
    auto csize = m_sp->getContentSize();
    this->setContentSize(csize);
    m_sp->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_sp);
    
    this->setCollideRect(Rect(0, 0, csize.width, csize.height));
    
    this->setScore(0);
    this->setJadeNum(1);
    this->setLocalZOrder(ZORDER_JADE);
    
    return true;
}

void Jade::times()
{
    Treasure::times();
    
    this->setJadeNum(this->getJadeNum()*2);
}

void Jade::bePicked()
{
    Treasure::bePicked();
    
    m_gameController->addJade(this->getJadeNum());
}