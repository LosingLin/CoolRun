//
//  Treasure.cpp
//  CoolRun
//
//  Created by ManYou on 15/7/1.
//
//

#include "Treasure.h"
#include "ActionHelp.h"
#include "Runner.h"
#include "AudioHelp.h"
#include "ActionHelp.h"

Treasure::Treasure()
: CollideNode()
, b_isAnimating(false)
, m_sp(nullptr)
, m_score(0)
, b_isTimed(false)
{
}
Treasure::~Treasure()
{
}

bool Treasure::init()
{
    
    if (!CollideNode::init())
    {
        return false;
    }
    
    this->setGravityEffect(false);
    this->setCollideEffect(true);
    this->setCollideType(kCollideTypeSimple);
    
    this->setLocalZOrder(ZORDER_COIN);
    
    return true;
}

void Treasure::onEnter()
{
    CollideNode::onEnter();
    
    //    this->schedule(schedule_selector(Treasure::update), 1);
    
    //m_sp->stopAllActions();
    
//    auto csize = m_sp->getContentSize();
//    this->setContentSize(csize);
    
}
void Treasure::onExit()
{
    //    this->unschedule(schedule_selector(Treasure::update));
    CollideNode::onExit();
}

void Treasure::times()
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

void Treasure::bePicked()
{
    //this->unschedule(schedule_selector(Treasure::update));
    AudioHelp::playBePickedEft();
    
    m_sp->stopAllActions();
    m_sp->removeFromParentAndCleanup(true);
    
    m_gameController->addScore(m_score);
    
    //    auto csize = this->getContentSize();
    //    auto psq = ParticleSystemQuad::create("Treasure.plist");
    //    psq->setPosition(Vec2(25, 25));
    //    this->addChild(psq);
    auto csize = this->getContentSize();
    auto sp = Sprite::createWithSpriteFrameName("coin_picked01.png");
    //int p = rand()%6 + 20;
    sp->setPosition(Vec2(csize.width/2, csize.height/2));
    auto spSize = sp->getContentSize();
    sp->setScale(csize.width/spSize.width + 0.5);
    this->addChild(sp);
    auto animate = ActionHelp::createFrameAction("coin_picked%02d.png", 1, 5, 0.2, true);
    sp->runAction(animate);
    auto delay = DelayTime::create(0.3f);
    auto call = CallFunc::create(CC_CALLBACK_0(Treasure::bePickedDone, this));
    this->runAction(Sequence::create(delay, call, NULL));
    //    sp->runAction(Sequence::create(animate, call, NULL));
}
void Treasure::bePickedDone()
{
    this->setDestoryed(true);
}


Treasure* Treasure::create(rapidjson::Value& _value)
{
    auto _Treasure = Treasure::create();
    _Treasure->loadJson(_value);
    _Treasure->debugShow();
    return _Treasure;
}

//bool Treasure::collided(PhysicNode* _runner)
//{
//    m_gameController->addTreasure(1);
//
//    return true;
//}

void Treasure::trackCollideWithRunner(Runner* _runner)
{
    //    log("Treasure track collide....");
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
                
                pos.x -= rect1.size.width/2;
                pos.y -= rect1.size.height/2;
                
                this->setPosition(pos);
                //                            auto moveTo = MoveTo::create(0.1, pos2);
                //                            this->runAction(moveTo);
            }
            
        }
        
        
        if (_runner->isTimesCoinING() && !b_isTimed)
        {
            auto timesTreasure_dis = _runner->getTimesCoinDistance();
            if (x_dis*x_dis + y_dis*y_dis < timesTreasure_dis*timesTreasure_dis)
            {
                
                this->times();
            }
            
        }
        
    }
    
}