//
//  TreasureBox.cpp
//  CoolRun
//
//  Created by ManYou on 15/6/23.
//
//

#include "TreasureBox.h"
#include "Runner.h"
#include "Bullet.h"
#include "AudioHelp.h"


TreasureBox::TreasureBox()
: Animal()
{
    
}
TreasureBox::~TreasureBox()
{
    
}

bool TreasureBox::init()
{
    if (!Animal::init())
    {
        return false;
    }
    this->setGravityEffect(true);
    this->setCollideEffect(true);
    this->setCollideType(kCollideTypeSimple);
    
    auto _sp = Sprite::createWithSpriteFrameName("treasureBoxClose.png");
    auto csize = _sp->getContentSize();
    this->setContentSize(csize);
    _sp->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(_sp);
    
    this->setCollideRect(Rect(0, 50, csize.width, csize.height-50));
    
    return true;
}

void TreasureBox::trackCollideWithRunner(Runner* _runner)
{
    auto rect1 = PhysicHelp::countPhysicNodeRect(this);
    auto rect2 = PhysicHelp::countPhysicNodeRect(_runner);
    if (CollideTrackHelp::trackCollide(rect1, rect2))
    {
        this->setDestoryed(true);
        m_gameController->addBox(1);
        AudioHelp::playBePickedEft();
        return;
    }
}
void TreasureBox::trackCollideWithBullet(Bullet* bullet)
{
    if (bullet->isAnimalHurt())
    {
        auto rect1 = PhysicHelp::countPhysicNodeRect(this);
        auto rect2 = PhysicHelp::countPhysicNodeRect(bullet);
        
        if (CollideTrackHelp::trackCollide(rect1, rect2))
        {
            bullet->setDestoryed(true);
            this->setDestoryed(true);
            m_gameController->addBox(1);
            AudioHelp::playBePickedEft();
            return;
        }
    }
}