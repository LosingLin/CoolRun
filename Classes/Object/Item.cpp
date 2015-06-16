//
//  Item.cpp
//  CoolRun
//
//  Created by ManYou on 14/12/20.
//
//

#include "Item.h"
#include "Runner.h"
#include "ActionHelp.h"


Item::Item()
: MultipleCollideNode()
, m_sp(nullptr)
, m_icon(nullptr)
, m_angle(0)
, m_maxY(0)
, m_orgY(0)
, m_angleSpeed(0)
, b_isFlying(false)
, m_flyVelcity(0.0f)
{
}
Item::~Item()
{
}

bool Item::init()
{
    if (!MultipleCollideNode::init())
    {
        return false;
    }
    this->setCollideEffect(true);
    this->setGravityEffect(false);
    this->setCollideType(CollideType::kCollideTypeSimple);
    
    m_sp = Sprite::createWithSpriteFrameName("kmd_01.png");
    auto csize = m_sp->getContentSize();
    this->setContentSize(csize);
    m_sp->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_sp);
    
    auto action = ActionHelp::createFrameAction("kmd_%02d.png", 1, 2, 0.8f);
    m_sp->runAction(action);
    
    this->setCollideRect(Rect(26, 60, csize.width-52, csize.height-64));
    
    this->debugShow();
    
    m_maxY = 100;
    m_angleSpeed = 0.04f;
    
    this->setLocalZOrder(ZORDER_ITEM);
    
    return true;
}

void Item::loadJson(rapidjson::Value& _value)
{
    MultipleCollideNode::loadJson(_value);
    
    if (_value.HasMember("fly_v")) {
        if (_value["fly_v"].IsDouble()) {
            auto fv = _value["fly_v"].GetDouble();
            this->setFlyVelcity(fv);
        }
    }
}
void Item::saveData(string* buffer)
{
    MultipleCollideNode::saveData(buffer);
    
    string str = string();
    stringstream ss;
    ss << "\"fly_v\":";
    ss << this->getFlyVelcity();
    ss << ",";
    ss >> str;
    buffer->append(str);
}

void Item::onEnter()
{
    MultipleCollideNode::onEnter();
    
    if (!this->isForEditor())
    {
        this->scheduleUpdate();
    }
    
    auto pos = this->getPosition();
    m_orgY = pos.y;
    
    //log("save xv %f", m_save_xv);
}
void Item::onExit()
{
    if (!this->isForEditor())
    {
        this->unscheduleUpdate();
    }
    MultipleCollideNode::onExit();
}
void Item::update(float delta)
{
    //log("item update delta : %f", delta);

    auto pos = this->getPosition();

    this->setPosition(Vec2(pos.x, m_orgY + m_maxY * sin(m_angle)));
    
    m_angle += m_angleSpeed;
    if (m_angle >= 360)
    {
        m_angle = 0;
    }
    
}


#pragma mark -
void Item::fly()
{
    auto xv = this->getXV();
    xv += this->getFlyVelcity();
    this->setXV(xv);
}
void Item::active(Runner* _runner)
{
    
}

#pragma mark - collide

void Item::trackCollideWithRunner(Runner* _runner)
{
    auto rect1 = PhysicHelp::countPhysicNodeRect(_runner);
    auto rect2 = PhysicHelp::countPhysicNodeRect(this);
    
    if (!b_isFlying)
    {
        bool isNear = CollideTrackHelp::isNearRight(rect1, rect2, 1200, true);
        if (isNear)
        {
            this->fly();
            b_isFlying = true;
        }
    }
    else
    {
        bool isAct = CollideTrackHelp::trackCollide(rect1, rect2);
        if (isAct)
        {
            this->setCollideEffect(false);
            this->active(_runner);            
        }
    }
}