//
//  BossBulletNet.cpp
//  CoolRun
//
//  Created by ManYou on 15/3/17.
//
//

#include "BossBulletNet.h"

BossBulletNet::BossBulletNet()
: Bullet()
, m_bullet(nullptr)
{
}
BossBulletNet::~BossBulletNet()
{
}

bool BossBulletNet::init()
{
    if (!Bullet::init())
    {
        return false;
    }
    this->setRunnerHurt(true);
    this->setAnimalHurt(false);
    this->setCollideEffect(true);
    this->setAtkable(true); 
    
    m_bullet = Sprite::createWithSpriteFrameName("bullet_net01.png");
    auto csize = m_bullet->getContentSize();
    this->setContentSize(csize);
    m_bullet->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_bullet);
    
    auto action = ActionHelp::createFrameAction("bullet_net%02d.png", 1, 4, 0.1);
    m_bullet->runAction(RepeatForever::create(action));
    
    //    m_particleSys = ParticleSystemQuad::create("poison.plist");
    //    m_particleSys->setPosition(Vec2(csize.width/2, csize.height/2));
    //    this->addChild(m_particleSys, -1);
    
    this->setCollideRect(Rect(10, 10, csize.width-20, csize.height-20));
    
    this->debugShow();
    
    return true;
}