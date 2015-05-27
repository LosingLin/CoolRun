//
//  MYSwitch.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/16.
//
//

#include "MYSwitch.h"
#include "GlobalDefined.h"


MYSwitch::MYSwitch()
: Node()
, m_onSp(nullptr)
, m_offSp(nullptr)
, m_innerBtn(nullptr)
, m_callback(nullptr)
, m_status(MYSwitchStatus::OFF)
{
    
}
MYSwitch::~MYSwitch()
{
    
}

bool MYSwitch::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    
    return true;
}

bool MYSwitch::initWithFrameName(const char* onspn, const char* offspn)
{
    if (!this->init())
    {
        return false;
    }
    this->setONSpriteWithFrameName(onspn);
    this->setOFFSpriteWithFrameName(offspn);
    
    auto csize = this->getContentSize();
    
    m_innerBtn = MYButton::createWithContentSize(csize);
    //m_innerBtn->setPosition(Vec2(csize.width, csize.height));
    m_innerBtn->addTouchEventListener(CC_CALLBACK_2(MYSwitch::innerBtnCallback, this));
    this->addChild(m_innerBtn);
    
    this->setStatus(MYSwitchStatus::ON);
    
    return true;
}

MYSwitch* MYSwitch::createWithFrameName(const char* onspn, const char* offspn)
{
    auto _switch = new MYSwitch();
    if (_switch && _switch->initWithFrameName(onspn, offspn))
    {
        _switch->autorelease();
        return _switch;
    }
    delete _switch;
    _switch = nullptr;
    return nullptr;
}

void MYSwitch::setONSpriteWithFrameName(const char* spfn)
{
    if (m_onSp)
    {
        m_onSp->removeFromParentAndCleanup(true);
        m_onSp = nullptr;
    }
    m_onSp = Sprite::createWithSpriteFrameName(spfn);
    auto csize = m_onSp->getContentSize();
    this->setContentSize(csize);
    m_onSp->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_onSp);
}

void MYSwitch::setOFFSpriteWithFrameName(const char* spfn)
{
    if (m_offSp)
    {
        m_offSp->removeFromParentAndCleanup(true);
        m_offSp = nullptr;
    }
    m_offSp = Sprite::createWithSpriteFrameName(spfn);
    auto csize = this->getContentSize();
    m_offSp->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_offSp);
}

void MYSwitch::setStatus(MYSwitchStatus status)
{
    if (m_status != status)
    {
        m_status = status;
        if (m_status == MYSwitchStatus::ON)
        {
            SAFESETVISIBLE(m_onSp, true);
            SAFESETVISIBLE(m_offSp, false);
        }
        else
        {
            SAFESETVISIBLE(m_onSp, false);
            SAFESETVISIBLE(m_offSp, true);
        }
    }
}

void MYSwitch::addSwitchCallback(MYSwitchCallback callback)
{
    m_callback = callback;
}

void MYSwitch::innerBtnCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        if (m_status == MYSwitchStatus::ON)
        {
            this->setStatus(MYSwitchStatus::OFF);
        }
        else
        {
            this->setStatus(MYSwitchStatus::ON);
        }
        
        if (m_callback)
        {
            m_callback(this, m_status);
        }
    }
}