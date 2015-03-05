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
    
    m_bullet = Sprite::createWithSpriteFrameName("bullet_poison.png");
    auto csize = Size(120, 62);
    this->setContentSize(csize);
    m_bullet->setPosition(Vec2(csize.width/2, csize.height/2));
    m_bullet->setScale(0.7);
    this->addChild(m_bullet);
    
    m_particleSys = ParticleSystemQuad::create("poison.plist");
    m_particleSys->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_particleSys, -1);
    
    this->setCollideRect(Rect(0, 0, csize.width, csize.height));
    
    this->debugShow();
    
    return true;
}