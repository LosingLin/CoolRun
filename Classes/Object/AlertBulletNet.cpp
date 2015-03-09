//
//  AlertBulletNet.cpp
//  CoolRun
//
//  Created by ManYou on 15/3/2.
//
//

#include "AlertBulletNet.h"

AlertBulletNet::AlertBulletNet()
: AlertBullet()
{
    
}
AlertBulletNet::~AlertBulletNet()
{
    
}

bool AlertBulletNet::init()
{
    if (!AlertBullet::init())
    {
        return false;
    }
    
    this->setRunnerHurt(true);
    this->setAnimalHurt(false);
    
    m_bullet = Sprite::createWithSpriteFrameName("bullet_net01.png");
    auto csize = m_bullet->getContentSize();
    this->setContentSize(csize);
    m_bullet->setPosition(Vec2(csize.width/2, csize.height/2));
    //m_bullet->setRotation(-90);
    this->addChild(m_bullet);
    
    auto action = ActionHelp::createFrameAction("bullet_net%02d.png", 1, 4, 0.1);
    m_bullet->runAction(RepeatForever::create(action));
    
//    m_particleSys = ParticleSystemQuad::create("net.plist");
//    m_particleSys->setPosition(Vec2(csize.width/2, csize.height/2));
//    this->addChild(m_particleSys, -1);
    
    this->setCollideRect(Rect(10, 10, csize.width-20, csize.height-20));
    
    this->debugShow();
    
    m_line = Sprite::createWithSpriteFrameName("alertline_03.png");
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