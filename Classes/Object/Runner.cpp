//
//  Runner.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-7.
//
//

#include "Runner.h"
#include <cstdio>
#include "CollideTrack.h"
#include "PhysicHelp.h"
#include "ActionHelp.h"
#include "Bullet.h"

Runner::Runner()
: CollideNode()
, m_state(kRunnerState_Unknown)
, m_actions(NULL)
, m_jumpCount(0)
, m_attckRect(Rect(0, 0, 0, 0))
, b_isAtk(false)
, b_isDad(false)
, b_isIgnoreLand(false)
, m_armature(nullptr)
, item_spareNum(0)
, item_currentSpareNum(0)
, item_spareNumLab(nullptr)
, item_isMagnetING(false)
, item_magnetDistance(0.0f)
, item_magnetLastTime(0.0f)
, item_isTimesCoinING(false)
, item_timesCoinDistance(0.0f)
, item_timesCoinLastTime(0.0f)
, item_isTimesJumpING(false)
, item_timesJumpTimes(0)
, item_timesJumpLastTime(0.0f)
, item_isDadING(false)
, item_dadLastTime(0.0f)
, item_isLandBuildING(false)
, item_buildLandLastTime(0.0f)
, item_isFlyING(false)
, item_flyLastTime(0.0f)
, item_buildLandIcon(nullptr)
, item_dadIcon(nullptr)
, item_flyIcon(nullptr)
, item_magnetIcon(nullptr)
, item_spareIcon(nullptr)
, item_timesCoinIcon(nullptr)
, item_timesJumpIcon(nullptr)
{
}
Runner::~Runner()   
{
    CC_SAFE_RELEASE_NULL(m_actions);
}

bool Runner::init()
{
    if (!CollideNode::init()) {
        return false;
    }

    m_armature = Armature::create("Runner");
    m_armature->setScale(0.36f);
    this->addChild(m_armature);
    
    auto csize = m_armature->getContentSize() * 0.36f;
    this->setContentSize(csize);
    
    m_armature->setPosition(Vec2(csize.width/2, csize.height/2));
    
    setRunnerState(kRunnerState_Running);
    
    SHOW_ORIGIN_AND_CONTENT;
    
    this->setGravityEffect(true);
    
    this->setCollideRect(Rect(2, 8, 86, 126));
    this->setCollideEffect(true);
    SHOW_RECT(this->getCollideRect());
    
    this->setLocalZOrder(ZORDER_RUNNER);
    
    //Item
    this->initItemData();
    item_spareNumLab = Label::createWithTTF("", "Marker Felt.ttf", 32);
    item_spareNumLab->setPosition(Vec2(10, 132));
    this->addChild(item_spareNumLab);
    
    return true;
}

void Runner::setRunnerState(RunnerState state)
{
    //CCASSERT(state >=0 && state < m_actions->count(), "state out of range!");

    if (m_state != state)
    {
        m_state = state;
        switch (m_state)
        {
            case kRunnerState_Running:
                m_armature->getAnimation()->play("run");
                break;
            case kRunnerState_JumpUp:
                m_armature->getAnimation()->play("jump");
                break;
            case kRunnerState_JumpUp2:
                m_armature->getAnimation()->play("fly");
                break;
            case kRunnerState_JumpDown:
                m_armature->getAnimation()->play("down");
                break;
            default:
                break;
        }
    }
    
}

void Runner::rebound()
{
    this->setJumpCount(0);
    this->setRunnerState(kRunnerState_JumpUp);
    this->setYA(0.0f);
    this->setYV(580.0f);
}

void Runner::jump()
{
    auto jumpCount = this->getJumpCount();  
    auto maxJumpCount = isTimesJumpING() ? item_timesJumpTimes : 2;
    if (jumpCount >= maxJumpCount) {
        return;
    }
    
    if (jumpCount >= 1)
    {
        this->setRunnerState(kRunnerState_JumpUp2);
        this->setYA(0.0f);
        this->setYV(680.0f);
    }
    else
    {
        this->setRunnerState(kRunnerState_JumpUp);
        this->setYA(0.0f);
        this->setYV(880.0f);
    }
    
    this->addJumpCount();
}

void Runner::attack()
{
    if (b_isAtk)
    {
        return;
    }
    
    b_isAtk = true;
    
    auto _sword = Sprite::createWithSpriteFrameName("attack.png");
    auto scsize = _sword->getContentSize();
    _sword->setAnchorPoint(Vec2(0.5, 0.5));
    _sword->setRotation(-30);
    
    auto csize = getContentSize();
    auto pos = Vec2(csize.width-10, csize.height/2+10);
    _sword->setPosition(pos);
    this->addChild(_sword);
    
    m_attckRect = Rect(pos.x-scsize.width/2+10, pos.y-scsize.height/2+10, scsize.width-20, scsize.height-20);
    static bool flag = false;
    if (!flag)
    {
        SHOW_RECT(m_attckRect);
        flag = true;
    }
    
    
    auto _rotation = RotateTo::create(0.1, 30, 30);
    auto _call = CallFunc::create(CC_CALLBACK_0(Runner::attackOver, this, _sword));
    auto _seq = Sequence::create(_rotation, _call, NULL);

    _sword->runAction(_seq);
}
void Runner::attackOver(Node* _sword)
{
    b_isAtk = false;
    _sword->removeFromParentAndCleanup(true);
}

void Runner::CollideTrackListener_CollideOnce(CollideDirection direction, PhysicNode *node)
{
    if (this->isIgnoreLand())
    {
        return;
    }
    
    auto rect1 = PhysicHelp::countPhysicNodeRect(node);
    auto rect2 = PhysicHelp::countPhysicNodeRect(this);
    
    if (direction == kCollideDirectionUp) {
        if (m_state != kRunnerState_Running) {
            //log("State = %d", m_state);
            this->setXA(0.0f);
            this->setXV(0.0f);
            this->setRunnerState(kRunnerState_Running);
        }
        auto dis = rect1.size.height - rect2.origin.y + rect1.origin.y;
        auto pos = this->getPosition();
        pos.y += dis;
//        if (pos.y < (pos.y + dis)) {
//            pos.y += (dis/2 - 1);
//        }
        this->setPosition(pos);
        auto ya = this->getYA();
        auto yv = this->getYV();
        if (ya < 0)
        {
            this->setYA(0.0f);
        }
        if (yv < 0)
        {
            this->setYV(0.0f);
        }
        
        this->setJumpCount(0);
        
        PhysicHelp::showTips("Up", this, Vec2(0, 0));
        
    }
    else if(direction == kCollideDirectionLeft) {
        PhysicHelp::showTips("Left", this, Vec2(0, 0));
        
        auto dis = rect2.size.width - rect1.origin.x + rect2.origin.x;
        
        auto pos = this->getPosition();
        pos.x -= dis;
        this->setPosition(pos);
        
//        if (m_state != kRunnerState_Crouch) {
//            this->setRunnerState(kRunnerState_Crouch);
//        }
        this->setXV(node->getXV());
        this->setXA(node->getXA());
    }
    else if(direction == kCollideDirectionDown)
    {
        //return;
        PhysicHelp::showTips("Down", this, Vec2(0, 0));
        
        auto dis = rect1.size.height - rect2.origin.y + rect1.origin.y;
        auto pos = this->getPosition();
        //pos.y -= dis;
        if (pos.y > (pos.y - dis)) {
            pos.y --;
        }
        this->setPosition(pos);
        
        this->setYA(0.0f);
        this->setYV(0.0f);
    }
}
void Runner::CollideTrackListener_CollideAll(CollideDirection direction)
{
    if (this->isIgnoreLand())
    {
        return;
    }
    
    if (direction == kCollideDirectionMiss) {
//        if (m_state != kRunnerState_JumpDown && m_state != kRunnerState_JumpUp) {
//            
//        }
        if (this->getYV() < 0)
        {
            this->setRunnerState(kRunnerState_JumpDown);
        }
        
        this->setXA(0.0f);
        this->setXV(0.0f);

    }
}

void Runner::trackCollideWithBullet(Bullet* bullet)
{
    auto rect1 = PhysicHelp::countPhysicNodeRect(bullet);
    auto rect2 = PhysicHelp::countPhysicNodeRect(this);
    
    bool isCollided = CollideTrackHelp::trackCollide(rect1, rect2);
    if (isCollided)
    {
        if (!this->isDad())
        {
            m_gameController->dead(this);
        }
        bullet->setDestoryed(true);
    }
}

#pragma mark - item
void Runner::initItemData()
{
    item_spareNum = 5;
    
    item_isMagnetING = false;
    item_magnetDistance = 400;
    item_magnetLastTime = 12.0f;
    
    item_isTimesCoinING = false;
    item_timesCoinDistance = 400;
    item_timesCoinLastTime = 12.0f;
    
    item_isTimesJumpING = false;
    item_timesJumpTimes = 3;
    item_timesJumpLastTime = 12.0f;
    
    item_isDadING = false;
    item_dadLastTime = 12.0f;
    
    item_isLandBuildING = false;
    item_buildLandLastTime = 12.0f;
    
    item_isFlyING = false;
    item_flyLastTime = 5.0f;
}
void Runner::displaySpareNum(int num)
{
    item_currentSpareNum = num;
    if (num <= 1)
    {
        if (item_spareIcon)
        {
            item_spareIcon->removeFromParentAndCleanup(true);
            item_spareIcon = nullptr;
        }
        item_spareNumLab->setString("");
        return;
    }
    if (!item_spareIcon)
    {
        item_spareIcon = Sprite::createWithSpriteFrameName("item_spare.png");
        item_spareIcon->setPosition(this->getIconPosition());
        this->addChild(item_spareIcon);
    }
    stringstream ss;
    ss << num;
    item_spareNumLab->setString(ss.str());
}

void Runner::startMagnet()
{
    this->setMagnetING(true);
    auto delay = DelayTime::create(item_magnetLastTime);
    auto call = CallFunc::create(CC_CALLBACK_0(Runner::endMagnet, this));
    this->runAction(Sequence::create(delay, call, NULL));
    if (!item_magnetIcon)
    {
        item_magnetIcon = Sprite::createWithSpriteFrameName("item_mag.png");
        item_magnetIcon->setPosition(this->getIconPosition());
        this->addChild(item_magnetIcon);
    }
    
}

void Runner::endMagnet()
{
    this->setMagnetING(false);
    if (item_magnetIcon)
    {
        item_magnetIcon->removeFromParentAndCleanup(true);
        item_magnetIcon = nullptr;
    }
}

void Runner::startTimesCoin()
{
    this->setTimesCoinING(true);
    auto delay = DelayTime::create(item_timesCoinLastTime);
    auto call = CallFunc::create(CC_CALLBACK_0(Runner::endTimesCoin, this));
    this->runAction(Sequence::create(delay, call, NULL));
    
    if (!item_timesCoinIcon)
    {
        item_timesCoinIcon = Sprite::createWithSpriteFrameName("item_timecoin.png");
        item_timesCoinIcon->setPosition(this->getIconPosition());
        this->addChild(item_timesCoinIcon);
    }
}
void Runner::endTimesCoin()
{
    this->setTimesCoinING(false);
    
    if (item_timesCoinIcon)
    {
        item_timesCoinIcon->removeFromParentAndCleanup(true);
        item_timesCoinIcon = nullptr;
    }
}

void Runner::startTimesJump()
{
    this->setTimesJumpING(true);
    auto delay = DelayTime::create(item_timesJumpLastTime);
    auto call = CallFunc::create(CC_CALLBACK_0(Runner::endTimesJump, this));
    this->runAction(Sequence::create(delay, call, NULL));
    
    if (!item_timesJumpIcon)
    {
        item_timesJumpIcon = Sprite::createWithSpriteFrameName("item_jump.png");
        item_timesJumpIcon->setPosition(this->getIconPosition());
        this->addChild(item_timesJumpIcon);
    }
}
void Runner::endTimesJump()
{
    this->setTimesJumpING(false);
    
    if (item_timesJumpIcon)
    {
        item_timesJumpIcon->removeFromParentAndCleanup(true);
        item_timesJumpIcon = nullptr;
    }
}

void Runner::startDad()
{
    this->setDadING(true);
    auto delay = DelayTime::create(item_dadLastTime);
    auto call = CallFunc::create(CC_CALLBACK_0(Runner::endDad, this));
    this->runAction(Sequence::create(delay, call, NULL));
    
    if (!item_dadIcon)
    {
        item_dadIcon = Sprite::createWithSpriteFrameName("item_dad.png");
        item_dadIcon->setPosition(this->getIconPosition());
        this->addChild(item_dadIcon);
    }
}
void Runner::endDad()
{
    this->setDadING(false);
    
    if (item_dadIcon)
    {
        item_dadIcon->removeFromParentAndCleanup(true);
        item_dadIcon = nullptr;
    }
}

void Runner::startLandBuild()
{
    this->setLandBuildING(true);
    auto delay = DelayTime::create(item_buildLandLastTime);
    auto call = CallFunc::create(CC_CALLBACK_0(Runner::endLandBuild, this));
    this->runAction(Sequence::create(delay, call, NULL));
    
    if (!item_buildLandIcon)
    {
        item_buildLandIcon = Sprite::createWithSpriteFrameName("item_buildland.png");
        item_buildLandIcon->setPosition(this->getIconPosition());
        this->addChild(item_buildLandIcon);
    }
}
void Runner::endLandBuild()
{
    this->setLandBuildING(false);
    
    if (item_buildLandIcon)
    {
        item_buildLandIcon->removeFromParentAndCleanup(true);
        item_buildLandIcon = nullptr;
    }
}

void Runner::startFly()
{
    if (this->isFlyING())
    {
        return;
    }
    this->setFlyING(true);
    auto delay = DelayTime::create(item_flyLastTime);
    auto call = CallFunc::create(CC_CALLBACK_0(Runner::endFly, this));
    auto delay1 = DelayTime::create(2.0f);
    auto call1 = CallFunc::create(CC_CALLBACK_0(Runner::endFlyEffect, this));
    this->runAction(Sequence::create(delay, call, delay1, call1, NULL));
    this->setGravityEffect(false);
    this->setYA(0.0f);
    this->setYV(0.0f);
    this->setDad(true);
    this->setIgnoreLand(true);
    this->setRunnerState(kRunnerState_JumpUp);
    this->setMagnetING(true);
    
//    m_gameController->setVelocity(3600);
    m_gameController->startFly();
    
    if (!item_flyIcon)
    {
        item_flyIcon = Sprite::createWithSpriteFrameName("item_fly.png");
        item_flyIcon->setPosition(this->getIconPosition());
        this->addChild(item_flyIcon);
    }
}
void Runner::endFly()
{
    this->setFlyING(false);
    this->setGravityEffect(true);
    this->setIgnoreLand(false);
    this->setMagnetING(false);
    this->setLandBuildING(true);
    
//    m_gameController->setVelocity(400);
    m_gameController->endFly();
}
void Runner::endFlyEffect()
{
    this->setDad(false);
    this->setLandBuildING(false);
    
    if (item_flyIcon)
    {
        item_flyIcon->removeFromParentAndCleanup(true);
        item_flyIcon = nullptr;
    }
}

const Vec2 Runner::getIconPosition()
{
    Vec2 pos = Vec2(0, 0);
    int count = 0;
    if (item_currentSpareNum > 1)
    {
        count++;
    }
    if (this->isMagnetING())
    {
        count++;
    }
    if (this->isTimesCoinING())
    {
        count++;
    }
    if (this->isTimesJumpING())
    {
        count++;
    }
    if (this->isDadING())
    {
        count++;
    }
    if (this->isLandBuildING())
    {
        count++;
    }
    if (this->isFlyING())
    {
        count++;
    }
    switch (count)
    {
        case 0:
            break;
        case 1:
        {
            pos.x = 10;
            pos.y = 126;
        }break;
        case 2:
        {
            pos.x = 46;
            pos.y = 140;
        }break;
        case 3:
        {
            pos.x = -10;
            pos.y = 96;
        }break;
        case 4:
        {
            pos.x = -26;
            pos.y = 56;
        }break;
        case 5:
        {
            pos.x = -10;
            pos.y = 16;
        }break;
        case 6:
        {
            pos.x = 10;
            pos.y = -26;
        }break;
        case 7:
        {
            pos.x = 86;
            pos.y = 146;
        }break;
            
        default:
            break;
    }
    return pos;
}