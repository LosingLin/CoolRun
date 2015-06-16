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
void BossBulletNet::beingDestoryed()
{
    this->setVelocityIgnore(true);
    this->removeAllChildrenWithCleanup(true);
    auto csize = this->getContentSize();
    auto broke01 = Sprite::createWithSpriteFrameName("bullet_net_broke01.png");
    broke01->setPosition(Vec2(csize.width/2 + 20, csize.height/2 -20));
    this->addChild(broke01);
    auto _moveBy = MoveBy::create(0.4, Vec2(30, -80));
    auto _fadeOut = FadeOut::create(0.4);
    auto _scale = ScaleTo::create(0.4, 1.2f);
    auto _spawn = Spawn::create(_moveBy, _fadeOut, _scale, NULL);
    auto _call = CallFunc::create(CC_CALLBACK_0(BossBulletNet::brokeDone, this));
    broke01->runAction(Sequence::create(_spawn, _call, NULL));
    
    auto broke02 = Sprite::createWithSpriteFrameName("bullet_net_broke02.png");
    broke02->setPosition(Vec2(csize.width/2 + 20, csize.height/2 + 20));
    this->addChild(broke02);
    _moveBy = MoveBy::create(0.4, Vec2(30, 80));
    _fadeOut = FadeOut::create(0.6);
    _scale = ScaleTo::create(0.4, 1.2f);
    _spawn = Spawn::create(_moveBy, _fadeOut, _scale, NULL);
    broke02->runAction(_spawn);
    
    auto broke03 = Sprite::createWithSpriteFrameName("bullet_net_broke03.png");
    broke03->setPosition(Vec2(csize.width/2 - 20, csize.height/2));
    this->addChild(broke03);
    _moveBy = MoveBy::create(0.4, Vec2(30, 40));
    _fadeOut = FadeOut::create(0.6);
    _scale = ScaleTo::create(0.4, 1.2f);
    _spawn = Spawn::create(_moveBy, _fadeOut, _scale, NULL);
    broke03->runAction(_spawn);
}

void BossBulletNet::brokeDone()
{
    this->setDestoryed(true);
}