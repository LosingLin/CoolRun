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
#include "ActionHelp.h"
#include "BoxData.h"
#include "BoxDataShowView.h"


TreasureBox::TreasureBox()
: Animal()
, m_boxSP(nullptr)
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
    
    m_boxSP = Sprite::createWithSpriteFrameName("box_01.png");
    auto csize = m_boxSP->getContentSize();
    this->setContentSize(csize);
    m_boxSP->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_boxSP);
    
    this->setCollideRect(Rect(0, 10, csize.width-30, csize.height-98));
    
    this->debugShow();
    this->setLocalZOrder(ZORDER_BOX);
    
    return true;
}

void TreasureBox::openBox()
{
    AudioHelp::playOpenDoorEft();
    this->setCollideEffect(false);
    auto _act = ActionHelp::createFrameAction("box_%02d.png", 1, 3, 0.1, false);
    auto _dely = DelayTime::create(0.5f);
    auto _call = CallFunc::create(CC_CALLBACK_0(TreasureBox::openBoxDone, this));
    m_boxSP->runAction(Sequence::create(_act, _dely, _call, NULL));
    
    auto _delay = DelayTime::create(0.1f);
    auto _showCall = CallFunc::create(CC_CALLBACK_0(TreasureBox::showBoxData, this));
    this->runAction(Sequence::create(_delay, _showCall, NULL));
}
void TreasureBox::openBoxDone()
{
    this->setDestoryed(true);
}
void TreasureBox::showBoxData()
{
    auto _boxData = m_gameController->openBox();
    
    m_gameController->addBoxData(_boxData);
    
    auto _showView = BoxDataShowView::create(_boxData);
    _showView->setAnchorPoint(Vec2(0.5, 0.5));
    auto csize = this->getContentSize();
    _showView->setPosition(Vec2(csize.width/2, csize.height/2 - 40));
    this->addChild(_showView);
    
    auto _mob = MoveBy::create(0.2, Vec2(0, 80));
    auto _scle = ScaleTo::create(0.2, 1.2);
    auto _spaw = Spawn::create(_mob, _scle, NULL);
    auto _fado = FadeOut::create(0.1);
    _showView->runAction(Sequence::create(_spaw, _fado, NULL));
}

void TreasureBox::trackCollideWithRunner(Runner* _runner)
{
    auto rect1 = PhysicHelp::countPhysicNodeRect(this);
    auto rect2 = PhysicHelp::countPhysicNodeRect(_runner);
    if (CollideTrackHelp::trackCollide(rect1, rect2))
    {
        if (kCollideDirectionUp == CollideTrackHelp::trackCollideDirection(rect1, rect2))
        {
            _runner->rebound();
        }
        this->openBox();
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
            this->openBox();
            return;
        }
    }
}