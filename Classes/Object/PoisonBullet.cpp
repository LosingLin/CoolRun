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
    
    m_bullet = Sprite::createWithSpriteFrameName("spider_bone/spider_belly_bullet.png");
    
    this->addChild(m_bullet);
    
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
            this->setContentSize(csize);
            m_bullet->setPosition(Vec2(csize.width/2, csize.height/2));

            this->setCollideRect(Rect(0, 0, csize.width, csize.height));
        }
            break;
        case kCRDirectionDown:
        {
            auto csize = m_bullet->getContentSize();
            this->setContentSize(csize);
            m_bullet->setPosition(Vec2(csize.width/2, csize.height/2));
            m_bullet->setRotation(180);
            this->setCollideRect(Rect(0, 0, csize.width, csize.height));
        }
            break;
        case kCRDirectionLeft:
        {
            auto csize = m_bullet->getContentSize();
            this->setContentSize(Size(csize.height, csize.width));
            m_bullet->setPosition(Vec2(csize.height/2, csize.width/2));
            m_bullet->setRotation(-90);
            this->setCollideRect(Rect(0, 0, csize.height, csize.width));
        }
            break;
        case kCRDirectionRight:
        {
            auto csize = m_bullet->getContentSize();
            this->setContentSize(Size(csize.height, csize.width));
            m_bullet->setPosition(Vec2(csize.height/2, csize.width/2));
            m_bullet->setRotation(90);
            this->setCollideRect(Rect(0, 0, csize.height, csize.width));
        }
            break;
            
        default:
            break;
    }
}