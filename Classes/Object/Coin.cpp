//
//  Coin.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-12.
//
//

#include "Coin.h"
#include "ActionHelp.h"
#include "Runner.h"
#include "AudioHelp.h"
#include "ActionHelp.h"

Coin::Coin()
: Treasure()
{
}
Coin::~Coin()
{
}

bool Coin::init()
{
    
    if (!CollideNode::init())
    {
        return false;
    }
    
    m_sp = Sprite::createWithSpriteFrameName("coin_00.png");
    auto csize = m_sp->getContentSize();
    this->setContentSize(csize);
    m_sp->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_sp);
    
    
    
    
    this->setCollideRect(Rect(0, 0, csize.width, csize.height));
    
    this->debugShow();
    
    this->setLocalZOrder(ZORDER_COIN);
    
    int random = rand() % 7;
    auto delay = DelayTime::create(random);
    auto action01 = ActionHelp::createFrameAction("coin_%02d.png", 0, 4, 0.1, false);
    auto action02 = ActionHelp::createFrameAction("coin_%02d.png", 4, 0, 0.1, false);
    auto sequence = Sequence::create(delay, action01, action02, NULL);
    m_sp->runAction(RepeatForever::create(sequence));
    
    this->setScore(1);
    
    return true;
}

void Coin::bePicked()
{
    this->setContentSize(m_sp->getContentSize());
    
    Treasure::bePicked();
}

/*

void Treasure::onEnter()
{
    Treasure::onEnter();
    
//    this->schedule(schedule_selector(Coin::update), 1);
    
    //m_sp->stopAllActions();
    
}
void Treasure::onExit()
{
//    this->unschedule(schedule_selector(Coin::update));
    CollideNode::onExit();
}


void Coin::update(float delta)
{
//    log("Coin ---- update : %f", delta);
    if (!m_sp)
    {
        return;
    }
    if (b_isAnimating)
    {
        return;
    }
    
    b_isAnimating = true;
    
    int mark = rand()%30;
    if (mark < 10)
    {
        auto action01 = ActionHelp::createFrameAction("coin_%02d.png", 0, 4, 0.1, false);
        auto action02 = ActionHelp::createFrameAction("coin_%02d.png", 4, 0, 0.1, false);
        m_sp->runAction(Sequence::create(action01, action02, CallFunc::create(CC_CALLBACK_0(Coin::acionDoneCallback, this)), NULL));
    }
    else if (mark == 11)
    {
        if (this->isForEditor())
        {
            return;
        }
        auto action01 = ScaleTo::create(0.5, 0.7);
        auto action02 = ScaleTo::create(0.5, 1);
        m_sp->runAction(Sequence::create(action01, action02, CallFunc::create(CC_CALLBACK_0(Coin::acionDoneCallback, this)), NULL));
    }
    else if (mark == 12)
    {
        auto action01 = DelayTime::create(2);
        m_sp->runAction(Sequence::create(action01, CallFunc::create(CC_CALLBACK_0(Coin::acionDoneCallback, this)), NULL));
    }
    else
    {
        if (this->isForEditor())
        {
            return;
        }
        auto pos = this->getPosition();
        int inc_x = rand()%4-2;
        int inc_y = rand()%4-2;
        pos.x += inc_x;
        pos.y += inc_y;
        
        auto action01 = MoveTo::create(0.5, pos);
        this->runAction(Sequence::create(action01, CallFunc::create(CC_CALLBACK_0(Coin::acionDoneCallback, this)), NULL));
    }
}
 */

Coin* Coin::create(rapidjson::Value& _value)
{
    auto _coin = Coin::create();
    _coin->loadJson(_value);
    _coin->debugShow();
    return _coin;
}