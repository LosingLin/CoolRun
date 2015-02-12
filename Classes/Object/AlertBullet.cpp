//
//  AlertBullet.cpp
//  CoolRun
//
//  Created by ManYou on 14/12/16.
//
//

#include "AlertBullet.h"


AlertBullet::AlertBullet()
: Bullet()
, m_bullet(nullptr)
, m_line(nullptr)
, m_alert(nullptr)
, b_isAlterted(false)
{
}
AlertBullet::~AlertBullet()
{
}

bool AlertBullet::init()
{
    if (!Bullet::init())
    {
        return false;
    }
    this->setRunnerHurt(true);
    this->setAnimalHurt(false);
    
    m_bullet = Sprite::createWithSpriteFrameName("spider_bone/spider_belly_bullet.png");
//    auto csize = m_bullet->getContentSize();
    auto csize = Size(170, 90);
    this->setContentSize(csize);
    m_bullet->setPosition(Vec2(csize.width/2, csize.height/2));
    m_bullet->setRotation(-90);
    this->addChild(m_bullet);
    
    this->setCollideRect(Rect(0, 0, csize.width, csize.height));
    
    this->debugShow();
    
    m_line = Sprite::createWithSpriteFrameName("alertline_02.png");
    m_line->setAnchorPoint(Vec2(1, 0.5));
    m_line->setPosition(Vec2(0, csize.height/2));
    this->addChild(m_line);
    
    m_alert = Sprite::createWithSpriteFrameName("Skill_n.png");
    auto asize = m_alert->getContentSize();
    m_alert->setPosition(Vec2(-asize.width*0.5f, csize.height/2));
    m_alert->setScale(0.5f);
    this->addChild(m_alert);
    
    m_line->setVisible(false);
    m_alert->setVisible(false);
    
    return true;
}

void AlertBullet::onEnter()
{
    Bullet::onEnter();
    
    if (!this->isForEditor())
    {
        this->scheduleUpdate();
    }
    
    
//    log("save xv:%f, xa:%f", m_save_xv, m_save_xa);
    
    
}
void AlertBullet::onExit()
{
    if (!this->isForEditor())
    {
        this->unscheduleUpdate();
    }
    
    Bullet::onExit();
}

void AlertBullet::alertDone()
{
    m_line->setVisible(false);
    m_alert->setVisible(false);

    this->setVelocityIgnore(false);
}

void AlertBullet::update(float delta)
{
    if (b_isAlterted)
    {
        return;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto pos = this->getPosition();
    if (pos.x <= origin.x + visibleSize.width)
    {
        this->setVelocityIgnore(true);
        
        pos.x = origin.x + visibleSize.width;
        this->setPosition(pos);
        
        m_line->setVisible(true);
        m_alert->setVisible(true);
        
        //auto fadeOut01 = FadeOut::create(0.5);
        auto scaleBy01 = ScaleBy::create(0.3, 1.2);
        //auto spawn01 = Spawn::create(fadeOut01, scaleBy01, NULL);
        
        //auto fadeIn01 = FadeOut::create(0.5);
        auto scaleBy02 = ScaleBy::create(0.3, 0.8);
        //auto spawn02 = Spawn::create(fadeIn01, scaleBy02, NULL);
        
        //auto fadeOut02 = FadeOut::create(0.5);
        auto scaleBy03 = ScaleBy::create(0.3, 1.4);
        //auto spawn03 = Spawn::create(fadeOut02, scaleBy03, NULL);
        
        auto delay = DelayTime::create(0.6);
        auto fadeOut = FadeOut::create(0.2);
        
        auto callback = CallFunc::create(CC_CALLBACK_0(AlertBullet::alertDone, this));
        //auto sequence = Sequence::create(spawn01, spawn02, spawn03, callback, NULL);
        
        auto sequence = Sequence::create(scaleBy01, scaleBy02, scaleBy03, delay, fadeOut, callback, NULL);
        
        m_alert->runAction(sequence);
        
        b_isAlterted = true;
    }
    
}