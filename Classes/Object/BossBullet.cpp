//
//  BossBullet.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/19.
//
//

#include "BossBullet.h"

BossBullet::BossBullet()
: Bullet()
, m_bullet(nullptr)
{
}
BossBullet::~BossBullet()
{
}

bool BossBullet::init()
{
    if (!Bullet::init())
    {
        return false;
    }
    this->setRunnerHurt(true);
    this->setAnimalHurt(false);
    this->setCollideEffect(true);
    
    m_bullet = Sprite::createWithSpriteFrameName("bullet_poison01.png");
    auto csize = m_bullet->getContentSize();
    this->setContentSize(csize);
    m_bullet->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_bullet);
    
    auto action = ActionHelp::createFrameAction("bullet_poison%02d.png", 1, 5, 0.1);
    m_bullet->runAction(RepeatForever::create(action));
    
//    m_particleSys = ParticleSystemQuad::create("poison.plist");
//    m_particleSys->setPosition(Vec2(csize.width/2, csize.height/2));
//    this->addChild(m_particleSys, -1);
    
    this->setCollideRect(Rect(0, 0, csize.width-20, csize.height));
    
    this->debugShow();
    
    return true;
}