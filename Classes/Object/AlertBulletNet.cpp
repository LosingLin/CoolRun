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
    
    this->setCollideRect(Rect(20, 20, csize.width-40, csize.height-40));
    
    this->debugShow();
    
    m_line = Sprite::createWithSpriteFrameName("alertline_03.png");
    m_line->setAnchorPoint(Vec2(1, 0.5));
    m_line->setPosition(Vec2(0, csize.height/2));
    this->addChild(m_line);
    
    m_alert = Sprite::createWithSpriteFrameName("exclamation_net.png");
    auto asize = m_alert->getContentSize();
    m_alert->setPosition(Vec2(-asize.width*0.5f, csize.height/2));
    m_alert->setScale(0.8f);
    this->addChild(m_alert);
    
    m_line->setVisible(false);
    m_alert->setVisible(false);
    
    
    return true;
}

void AlertBulletNet::beingDestoryed()
{
    //m_bullet->removeFromParentAndCleanup(true);
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
    auto _call = CallFunc::create(CC_CALLBACK_0(AlertBulletNet::brokeDone, this));
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

void AlertBulletNet::brokeDone()
{
    this->setDestoryed(true);
}