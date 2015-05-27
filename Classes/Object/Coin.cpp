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

Coin::Coin()
: CollideNode()
, b_isAnimating(false)
, m_sp(nullptr)
, m_score(0)
, b_isTimed(false)
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
    
    int random = rand() % 3;
    auto delay = DelayTime::create(random);
    auto action01 = ActionHelp::createFrameAction("coin_%02d.png", 0, 4, 0.1, false);
    auto action02 = ActionHelp::createFrameAction("coin_%02d.png", 4, 0, 0.1, false);
    auto sequence = Sequence::create(delay, action01, action02, NULL);
    m_sp->runAction(RepeatForever::create(sequence));
    
    m_score = 1;
    
    return true;
}

void Coin::onEnter()
{
    CollideNode::onEnter();
    
//    this->schedule(schedule_selector(Coin::update), 1);
    
    //m_sp->stopAllActions();
    
}
void Coin::onExit()
{
//    this->unschedule(schedule_selector(Coin::update));
    CollideNode::onExit();
}

void Coin::removeAllChildrenWithCleanup(bool clear)
{
    CollideNode::removeAllChildrenWithCleanup(clear);
    m_sp = nullptr;
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

void Coin::acionDoneCallback()
{
    b_isAnimating = false;
}

void Coin::times()
{
    this->setContentSize(m_sp->getContentSize());
    
    m_score = m_score*2;
    b_isTimed = true;
    
    float ssize = 1.2f;
    this->setScale(ssize);
    auto csize = this->getContentSize();
    this->setContentSize(Size(csize.width * ssize, csize.height * ssize));
    m_sp->setPosition(Vec2(csize.width/2, csize.height/2));
    this->setCollideRect(Rect(0, 0, csize.width * ssize, csize.height * ssize));
    this->debugShow();
}

void Coin::bePicked()
{
    //this->unschedule(schedule_selector(Coin::update));
    
    int r = rand()%3 + 1;
    char name[20] = {'\0'};
    sprintf(name, "coin_%02d.mp3", r);
    AudioHelp::playEft(name);
    
    m_sp->stopAllActions();
    m_sp->removeFromParentAndCleanup(true);
    
    m_gameController->addScore(m_score);
    
    auto csize = this->getContentSize();
    auto psq = ParticleSystemQuad::create("coin.plist");
    psq->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(psq);
    
    auto delay = DelayTime::create(0.4);
    auto call = CallFunc::create(CC_CALLBACK_0(Coin::bePickedDone, this));
    this->runAction(Sequence::create(delay, call, NULL));
}
void Coin::bePickedDone()
{
    this->setDestoryed(true);
    this->removeAllChildrenWithCleanup(true);
}


Coin* Coin::create(rapidjson::Value& _value)
{
    auto _coin = Coin::create();
    _coin->loadJson(_value);
    _coin->debugShow();
    return _coin;
}

//bool Coin::collided(PhysicNode* _runner)
//{
//    m_gameController->addCoin(1);
//    
//    return true;
//}

void Coin::trackCollideWithRunner(Runner* _runner)
{
//    log("Coin track collide....");
    auto rect1 = PhysicHelp::countPhysicNodeRect(this);
    auto rect2 = PhysicHelp::countPhysicNodeRect(_runner);
    
    auto isCollide = CollideTrackHelp::trackCollide(rect1, rect2);
    
    if (isCollide)
    {
        
        this->setCollideEffect(false);
        this->bePicked();
        return;
    }
    
    if (this->isVelocityIgnore())
    {
        this->setVelocityIgnore(false);
    }

    //处理磁铁和加倍
    if(_runner->isMagnetING() || _runner->isTimesCoinING())
    {
        auto pos1 = Vec2(rect1.origin.x + rect1.size.width/2, rect1.origin.y + rect1.size.height/2);
        auto pos2 = Vec2(rect2.origin.x + rect2.size.width/2, rect2.origin.y + rect2.size.height/2);
        
        auto x_dis = pos1.x - pos2.x;
        auto y_dis = pos1.y - pos2.y;
        
        if (_runner->isMagnetING())
        {
            auto magnet_dis = _runner->getMagnetDistance();
            
            if (x_dis*x_dis + y_dis*y_dis < magnet_dis*magnet_dis)
            {
                this->setVelocityIgnore(true);
                auto pos = this->getPosition();
                
//                if (_runner->isFlyING())
//                {
//                    float inc = 80;
//                    
//                    if (x_dis > 10)
//                    {
//                        pos.x -= abs(x_dis) > inc ? inc : abs(x_dis);
//                    }
//                    else if (x_dis < -10)
//                    {
//                        pos.x += abs(x_dis) > inc ? inc : abs(x_dis);
//                    }
//                    if (y_dis > 20)
//                    {
//                        pos.y -= abs(x_dis) > inc ? inc : abs(x_dis);
//                    }
//                    else if (y_dis < -20)
//                    {
//                        pos.y += abs(x_dis) > inc ? inc : abs(x_dis);
//                    }
//                }
//                else
//                {
//                    float inc = 10;
//                    if (x_dis > 10)
//                    {
//                        pos.x -= abs(x_dis) > inc ? inc : abs(x_dis);
//                    }
//                    else if (x_dis < -10)
//                    {
//                        pos.x += abs(x_dis) > inc ? inc : abs(x_dis);
//                    }
//                    if (y_dis > 20)
//                    {
//                        pos.y -= abs(x_dis) > inc ? inc : abs(x_dis);
//                    }
//                    else if (y_dis < -20)
//                    {
//                        pos.y += abs(x_dis) > inc ? inc : abs(x_dis);
//                    }
//                }
                
                float k = (pos1.y - pos2.y) / (pos1.x - pos2.x);
                //float b = pos1.y - k*pos1.x;
                float vel = 20.0f;
                
                if (_runner->isFlyING())
                {
                    vel = 60.0f;
                }
//                if (abs(pos1.y - pos2.y) < vel)
//                {
//                    vel = abs(pos1.y - pos2.y);
//                }
//                if (pos1.y > pos2.y)
//                {
////                    pos.x -= vel;
////                    pos.y = k*pos.x + b;
//                    vel = -vel;
//                    
//                }
//                pos.y += vel;
//                pos.x = vel / k + pos1.x;
                
                if (abs(pos1.x - pos2.x) < vel)
                {
                    vel = abs(pos1.x - pos2.x);
                }
                if (pos1.x > pos2.x)
                {
//                    pos.x -= vel;
//                    pos.y = k*pos.x + b;
                    vel = -vel;
                    
                }
                pos.x += vel;
                pos.y = vel * k + pos1.y;
                
                
                this->setPosition(pos);
//                            auto moveTo = MoveTo::create(0.1, pos2);
//                            this->runAction(moveTo);
            }

        }

        
        if (_runner->isTimesCoinING() && !b_isTimed)
        {
            auto timesCoin_dis = _runner->getTimesCoinDistance();
            if (x_dis*x_dis + y_dis*y_dis < timesCoin_dis*timesCoin_dis)
            {
                
                this->times();
            }
            
        }
        
    }

}
