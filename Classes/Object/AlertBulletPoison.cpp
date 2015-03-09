//
//  AlertBulletPoison.cpp
//  CoolRun
//
//  Created by ManYou on 15/3/2.
//
//

#include "AlertBulletPoison.h"

AlertBulletPoison::AlertBulletPoison()
: AlertBullet()
{
    
}
AlertBulletPoison::~AlertBulletPoison()
{
    
}

bool AlertBulletPoison::init()
{
    if (!AlertBullet::init())
    {
        return false;
    }
    
    this->setRunnerHurt(true);
    this->setAnimalHurt(false);
    
    m_bullet = Sprite::createWithSpriteFrameName("bullet_poison01.png");
    auto csize = m_bullet->getContentSize();
    this->setContentSize(csize);
    m_bullet->setPosition(Vec2(csize.width/2, csize.height/2));
    //m_bullet->setRotation(-90);
    this->addChild(m_bullet);
    
    auto action = ActionHelp::createFrameAction("bullet_poison%02d.png", 1, 5, 0.1);
    m_bullet->runAction(RepeatForever::create(action));
    
//    m_particleSys = ParticleSystemQuad::create("poison.plist");
//    m_particleSys->setPosition(Vec2(csize.width/2, csize.height/2));
//    this->addChild(m_particleSys, -1);
//    auto psize = m_particleSys->getContentSize();
//    log("PARTICLE : ----------------->%f, %f", psize.width, psize.height);
    
//    auto spframe = Director::getInstance()->getTextureCache()->getTextureForKey("particle_poison.png");
//    auto sp = Sprite::createWithTexture(spframe);
//    psize = sp->getContentSize();
//    log("SP : ----------------->%f, %f", psize.width, psize.height);
//    this->addChild(sp);
    
    this->setCollideRect(Rect(0, 0, csize.width-10, csize.height));
    
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