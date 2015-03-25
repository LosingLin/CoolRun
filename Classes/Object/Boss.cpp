//
//  Boss.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/15.
//
//

#include "Boss.h"
#include "SpiderKind.h"
#include "BossBullet.h"

Boss::Boss()
: Animal()
, m_hpBar(nullptr)
, m_armature(nullptr)
, b_isReady(false)
, b_isAtking(false)
, m_atkIndex(0)
{
    
}
Boss::~Boss()
{
    this->destoryRes();
}

bool Boss::init()
{
    if (!Animal::init())
    {
        return false;
    }
    
    this->initRes();
    
    return true;
}

Bullet* Boss::createShotBullet(int index)
{
    auto bullet = BossBullet::create();
    return bullet;
}
void Boss::shot(const Vec2& pos, float vel, int bulIndex)
{
    auto _bullet = this->createShotBullet(bulIndex);
    _bullet->setPosition(pos);
    auto v = m_gameController->getVelocity();
    _bullet->setXV(-v + vel);
    m_gameController->addBullet(_bullet);
}
Spider* Boss::createBornSpider(int index)
{
    auto spd = SpiderKind::create();
    return spd;
}
void Boss::bornSpider(const Vec2& pos, float vel, int spdIndex)
{
    auto spider = this->createBornSpider(spdIndex);
    spider->setState(SpiderState::kSpiderState_Walk);
    spider->setPosition(pos);
    auto v = m_gameController->getVelocity();
    spider->setXV(-v + vel);
    m_gameController->addSpider(spider);
}