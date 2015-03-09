//
//  PoisonBullet.cpp
//  CoolRun
//
//  Created by ManYou on 14/12/5.
//
//

#include "PoisonBullet.h"


PoisonBullet::PoisonBullet()
: Bullet()
, m_atkDirection(kCRDirectionUp)
, m_bullet(nullptr)
{
}
PoisonBullet::~PoisonBullet()
{
}

bool PoisonBullet::init()
{
    if (!Bullet::init())
    {
        return false;
    }
    this->setRunnerHurt(true);
    this->setAnimalHurt(true);
    this->setCollideEffect(true);
    
    m_bullet = Sprite::createWithSpriteFrameName("bullet_poison01.png");
    auto csize = m_bullet->getContentSize();
    this->setContentSize(csize);
//    m_bullet->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_bullet);
    
    auto action = ActionHelp::createFrameAction("bullet_poison%02d.png", 1, 5, 0.1);
    m_bullet->runAction(RepeatForever::create(action));
    
    
//    m_particleSys = ParticleSystemQuad::create("poison.plist");
//    m_particleSys->setPosition(Vec2(csize.width/2, csize.height/2));
//    this->addChild(m_particleSys, -1);
    
    this->debugShow();
    
    return true;
}

void PoisonBullet::setAtkDirection(CRDirection direction)
{
    m_atkDirection = direction;
    switch (m_atkDirection)
    {
        case kCRDirectionUp:
        {
            auto csize = m_bullet->getContentSize();
            this->setContentSize(Size(csize.height, csize.width));
            m_bullet->setPosition(Vec2(csize.height/2, csize.width/2));
            m_bullet->setRotation(90);
            this->setCollideRect(Rect(0, 0, csize.height, csize.width));
        }
            break;
        case kCRDirectionDown:
        {
            auto csize = m_bullet->getContentSize();
            this->setContentSize(Size(csize.height, csize.width));
            m_bullet->setPosition(Vec2(csize.height/2, csize.width/2));
            m_bullet->setRotation(-90);
            this->setCollideRect(Rect(0, 0, csize.height, csize.width));
        }
            break;
        case kCRDirectionLeft:
        {
            auto csize = m_bullet->getContentSize();
            this->setContentSize(Size(csize.width, csize.height));
            m_bullet->setPosition(Vec2(csize.width/2, csize.height/2));
            this->setCollideRect(Rect(0, 0, csize.width, csize.height));
        }
            break;
        case kCRDirectionRight:
        {
            auto csize = m_bullet->getContentSize();
            this->setContentSize(Size(csize.width, csize.height));
            m_bullet->setPosition(Vec2(csize.width/2, csize.height/2));
            m_bullet->setRotation(180);
            this->setCollideRect(Rect(0, 0, csize.width, csize.height));
        }
            break;
            
        default:
            break;
    }
}