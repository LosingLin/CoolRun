//
//  HpBar.cpp
//  CoolRun
//
//  Created by ManYou on 15/2/24.
//
//

#include "HpBar.h"

HpBar::HpBar()
: Node()
, m_totalHp(0.0f)
, m_currentHp(0.0f)
, m_bg01(nullptr)
, m_bg02(nullptr)
{
    
}
HpBar::~HpBar()
{
    
}

bool HpBar::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    auto frame = Sprite::createWithSpriteFrameName("hp_frame.png");
    auto csize = frame->getContentSize();
    this->setContentSize(csize);
    frame->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(frame);
    
    m_bg01 = ProgressTimer::create(Sprite::createWithSpriteFrameName("hp_bg01.png"));
    m_bg01->setType(ProgressTimer::Type::BAR);
    m_bg01->setMidpoint(Vec2(0, 0));
    m_bg01->setBarChangeRate(Vec2(1, 0));
    m_bg01->setZOrder(-1);
    m_bg01->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_bg01);
    m_bg02 = ProgressTimer::create(Sprite::createWithSpriteFrameName("hp_bg02.png"));
    m_bg02->setType(ProgressTimer::Type::BAR);
    m_bg02->setMidpoint(Vec2(0, 0));
    m_bg02->setBarChangeRate(Vec2(1, 0));
    m_bg02->setZOrder(-2);
    m_bg02->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_bg02);
    m_bg01->setPercentage(100);
    m_bg02->setPercentage(100);
    return true;
}

bool HpBar::init(float totalHp)
{
    if (!this->init())
    {
        return false;
    }
    
    m_totalHp = totalHp;
    m_currentHp = totalHp;
    
    auto csize = this->getContentSize();
    auto inc_x = csize.width / m_totalHp;
    auto x = 0.0f;
    auto y = csize.height/2;
    for (int i = 0; i < m_totalHp-1; ++ i)
    {
        auto spit = Sprite::createWithSpriteFrameName("hp_spit.png");
        spit->setPosition(Vec2(x + inc_x, y));
        this->addChild(spit);
        
        x += inc_x;
    }
    
    return true;
}

void HpBar::setCurrentHp(float hp)
{
    m_currentHp = hp;
    
    this->barUpdate();
}

void HpBar::barUpdate()
{
    float percentage = m_currentHp/m_totalHp * 100;
    m_bg01->runAction(ProgressTo::create(0.4, percentage));
    
    m_bg02->runAction(Sequence::create(DelayTime::create(0.2),
                                       ProgressTo::create(0.4, percentage),
                                       CallFunc::create(CC_CALLBACK_0(HpBar::check, this)),
                                       NULL));
}
void HpBar::delayUpdate()
{
    float percentage = m_currentHp/m_totalHp * 100;
    m_bg02->setPercentage(percentage);
}
void HpBar::check()
{
    if (m_currentHp <= 0)
    {
        this->removeFromParentAndCleanup(true);
    }
}

HpBar* HpBar::create(float totalHp)
{
    auto bar =  new HpBar();
    if (bar && bar->init(totalHp))
    {
        bar->autorelease();
        return bar;
    }
    delete bar;
    return nullptr;
}

