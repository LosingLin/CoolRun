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
#include "AudioHelp.h"

Runner::Runner()
: CollideNode()
, m_state(kRunnerState_Unknown)
, m_actions(NULL)
, m_jumpCount(0)
, m_attckRect(Rect(0, 0, 0, 0))
, m_headRect(Rect(0, 0, 0, 0))
, m_bodyRect(Rect(0, 0, 0, 0))
, m_legRect(Rect(0, 0, 0, 0))
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
, item_magnetCurrentTime(0.0f)
, item_isTimesCoinING(false)
, item_timesCoinDistance(0.0f)
, item_timesCoinLastTime(0.0f)
, item_timesCoinCurrentTime(0.0f)
, item_isTimesJumpING(false)
, item_timesJumpTimes(0)
, item_timesJumpLastTime(0.0f)
, item_timesJumpCurrentTime(0.0f)
, item_isDadING(false)
, item_dadLastTime(0.0f)
, item_dadCurrentTime(0.0f)
, item_isLandBuildING(false)
, item_buildLandLastTime(0.0f)
, item_buildLandCurrentTime(0.0f)
, item_isFlyING(false)
, item_isEndFlyING(false)
, item_flyLastTime(0.0f)
, item_flyCurrentTime(0.0f)
, item_isRebornING(false)
, item_rebornLastTime(0.0f)
, item_rebornCurrentTime(0.0f)
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
    
    this->setCollideRect(Rect(2, 8, 86, 122));
    this->setCollideEffect(true);
    SHOW_RECT(this->getCollideRect());
    
    this->setLocalZOrder(ZORDER_RUNNER);
    
    //Item
    this->initItemData();
    item_spareNumLab = Label::createWithSystemFont("", "", 32);
    item_spareNumLab->setPosition(Vec2(10, 132));
    this->addChild(item_spareNumLab);
    
    return true;
}

void Runner::onEnter()
{
    CollideNode::onEnter();
    
    Director::getInstance()->getScheduler()->schedule(schedule_selector(Runner::update), this, 0.0f, kRepeatForever, 0.01f, false);
}

void Runner::onEnterTransitionDidFinish()
{
    CollideNode::onEnterTransitionDidFinish();
}
void Runner::update(float delta)
{
    this->itemUpdate(delta);
}

void Runner::setRunnerState(RunnerState state)
{
    //CCASSERT(state >=0 && state < m_actions->count(), "state out of range!");

    if (m_state != state)
    {
//        if (m_state == kRunnerState_JumpDown && state == kRunnerState_Running)
//        {
//            AudioHelp::playEft("runner_land.mp3");
//        }
        m_state = state;
        switch (m_state)
        {
            case kRunnerState_Running:
                m_armature->getAnimation()->play("run");
                this->setCollideRect(Rect(2, 8, 86, 122));
                m_headRect = Rect(32, 90, 50, 42);
                m_bodyRect = Rect(20, 50, 40, 40);
                m_legRect = Rect(6, 20, 48, 40);
//                this->showRect(m_headRect);
//                this->showRect(m_bodyRect);
//                this->showRect(m_legRect);
                break;
            case kRunnerState_JumpUp:
                m_armature->getAnimation()->play("jump");
                this->setCollideRect(Rect(2, 8, 86, 122));
                m_headRect = Rect(22, 90, 50, 42);
                m_bodyRect = Rect(20, 50, 40, 40);
                m_legRect = Rect(16, 20, 38, 40);
//                this->showRect(m_headRect);
//                this->showRect(m_bodyRect);
//                this->showRect(m_legRect);
                break;
            case kRunnerState_JumpUp2:
                m_armature->getAnimation()->play("fly");
                this->setCollideRect(Rect(4, 26, 86, 90));
                //this->showRect(Rect(2, 26, 86, 90));
                m_headRect = Rect(2, 26, 86, 90);
                m_bodyRect = Rect(2, 26, 86, 90);
                m_legRect = Rect(2, 26, 86, 90);
                break;
            case kRunnerState_JumpDown:
                m_armature->getAnimation()->play("down");
                this->setCollideRect(Rect(2, 8, 86, 122));
                m_headRect = Rect(12, 90, 50, 42);
                m_bodyRect = Rect(20, 50, 40, 40);
                m_legRect = Rect(36, 20, 38, 40);
//                this->showRect(m_headRect);
//                this->showRect(m_bodyRect);
//                this->showRect(m_legRect);
                break;
            default:
                break;
        }
    }
    
}

void Runner::rebound()
{
    if (this->isFlyING())
    {
        return;
    }
    AudioHelp::playEft("runner_rebound.mp3");
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
    
    AudioHelp::playEft("runner_atk.mp3");
    
    b_isAtk = true;
    
    auto _sword = Sprite::createWithSpriteFrameName("runner_bone/attack.png");
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
        
        auto dis = rect2.size.height + rect2.origin.y - rect1.origin.y;
        auto pos = this->getPosition();
        pos.y -= dis;
//        if (pos.y > (pos.y - dis)) {
//            pos.y --;
//        }
        this->setPosition(pos);
        
        this->setYA(0.0f);
//        auto yv = this->getYV();
//        this->setYV(-yv);
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
    if (!bullet->isCollideEffect() || bullet->isDestoryed())
    {
        return;
    }
    auto rect1 = PhysicHelp::countPhysicNodeRect(bullet);
    auto rect2 = PhysicHelp::countPhysicNodeRect(this);
    if (this->isAtk() && bullet->isAtkable())
    {
        auto rect3 = PhysicHelp::countPhysicNodeRect(this, this->getAtkRect());
        bool isAtked = CollideTrackHelp::trackCollide(rect1, rect3);
        if (isAtked)
        {
            bullet->setCollideEffect(false);
            bullet->beingDestoryed();
            m_gameController->addScore(5);
            return;
        }
    }
    bool isCollided = CollideTrackHelp::trackCollide(rect1, rect2);
    if (isCollided)
    {
        if (!this->isDad() && !this->isRebornING())
        {
            m_gameController->dead(this);
        }
        bullet->setCollideEffect(false);
        bullet->setDestoryed(true);
    }
}

bool Runner::isCollidedWithTrueBody(const Rect& rect)
{
    auto headRect = PhysicHelp::countPhysicNodeRect(this, m_headRect);
    if (CollideTrackHelp::trackCollide(rect, headRect))
    {
        return true;
    }
    auto bodyRect = PhysicHelp::countPhysicNodeRect(this, m_bodyRect);
    if (CollideTrackHelp::trackCollide(rect, bodyRect))
    {
        return true;
    }
    auto legRect = PhysicHelp::countPhysicNodeRect(this, m_legRect);
    if (CollideTrackHelp::trackCollide(rect, legRect))
    {
        return true;
    }
    return false;
}
CollideDirection Runner::getDirectionWithTrueBody(const Rect& rect)
{
    auto headRect = PhysicHelp::countPhysicNodeRect(this, m_headRect);
    auto headDir = CollideTrackHelp::trackCollideDirection(rect, headRect);
    auto bodyRect = PhysicHelp::countPhysicNodeRect(this, m_bodyRect);
    auto bodyDir = CollideTrackHelp::trackCollideDirection(rect, bodyRect);
    auto legRect = PhysicHelp::countPhysicNodeRect(this, m_legRect);
    auto legDir = CollideTrackHelp::trackCollideDirection(rect, legRect);
    if (headDir == kCollideDirectionMiss && bodyDir == kCollideDirectionMiss && legDir == kCollideDirectionUp)
    {
        return kCollideDirectionUp;
    }
    else if((headDir == kCollideDirectionMiss || headDir == kCollideDirectionRight)
            && (bodyDir == kCollideDirectionMiss || bodyDir == kCollideDirectionRight)
            && (legDir == kCollideDirectionMiss || legDir == kCollideDirectionRight))
    {
        return kCollideDirectionMiss;
    }
    else
    {
        return kCollideDirectionLeft; 
    }
}

#pragma mark - item
void Runner::itemUpdate(float delta)
{
    if (item_magnetCurrentTime > 0.0f)
    {
        item_magnetCurrentTime -= delta;
        m_gameController->updatePowerIcon(PowerIcon::PowerType::MAGNET, item_magnetCurrentTime/item_magnetLastTime*100);
        if (item_magnetCurrentTime <= 0)
        {
            this->endMagnet();
        }
    }
    if (item_timesCoinCurrentTime > 0.0f)
    {
        item_timesCoinCurrentTime -= delta;
        m_gameController->updatePowerIcon(PowerIcon::PowerType::TIMESCOIN, item_timesCoinCurrentTime/item_timesCoinLastTime*100);
        if (item_timesCoinCurrentTime <= 0)
        {
            this->endTimesCoin();
        }
    }
    if (item_timesJumpCurrentTime > 0.0f)
    {
        item_timesJumpCurrentTime -= delta;
        m_gameController->updatePowerIcon(PowerIcon::PowerType::TIMESJUMP, item_timesJumpCurrentTime/item_timesJumpLastTime*100);
        if (item_timesJumpCurrentTime <= 0)
        {
            this->endTimesJump();
        }
    }
    if (item_dadCurrentTime > 0.0f)
    {
        item_dadCurrentTime -= delta;
        m_gameController->updatePowerIcon(PowerIcon::PowerType::DAD, item_dadCurrentTime/item_dadLastTime*100);
        if (item_dadCurrentTime <= 0)
        {
            this->endDad();
        }
    }
    if (item_buildLandCurrentTime > 0.0f)
    {
        item_buildLandCurrentTime -= delta;
        m_gameController->updatePowerIcon(PowerIcon::PowerType::LANDBUILD, item_buildLandCurrentTime/item_buildLandLastTime*100);
        if (item_buildLandCurrentTime <= 0)
        {
            this->endLandBuild();
        }
    }
    if (item_flyCurrentTime > 0.0f)
    {
        item_flyCurrentTime -= delta;
        m_gameController->updatePowerIcon(PowerIcon::PowerType::FLY, item_flyCurrentTime/item_flyLastTime*100);
        if (item_flyCurrentTime <= 0)
        {
            this->endFlyEffect();
        }
        else if (item_flyCurrentTime <= 1)
        {
            this->endFly();
        }
    }
    if (item_rebornCurrentTime > 0.0f)
    {
        item_rebornCurrentTime -= delta;
        m_gameController->updatePowerIcon(PowerIcon::PowerType::REBORN, item_rebornCurrentTime/item_rebornLastTime*100);
        if (item_rebornCurrentTime <= 0)
        {
            this->endReborn();
        }
    }
}
void Runner::initItemData()
{
    item_spareNum = 3;
    
    item_isMagnetING = false;
    item_magnetDistance = 500;
    item_magnetLastTime = 4.2f;
    
    item_isTimesCoinING = false;
    item_timesCoinDistance = 500;
    item_timesCoinLastTime = 4.6f;
    
    item_isTimesJumpING = false;
    item_timesJumpTimes = 3; 
    item_timesJumpLastTime = 5.0f;
    
    item_isDadING = false;
    item_dadLastTime = 4.0f;
    
    item_isLandBuildING = false;
    item_buildLandLastTime = 5.0f;
    
    item_isFlyING = false;
    item_flyLastTime = 3.0f;
    
    item_isRebornING = false;
    item_rebornLastTime = 3.0f;
    item_rebornCurrentTime = 0.0f;
}

void Runner::clearAllItemBuffers()
{
    item_magnetCurrentTime = 0;
    item_timesCoinCurrentTime = 0;
    item_timesJumpCurrentTime = 0;
    item_dadCurrentTime = 0;
    item_buildLandCurrentTime = 0;
    item_flyCurrentTime = 0;
    
    this->endMagnet();
    this->endTimesCoin();
    this->endTimesJump();
    this->endDad();
    this->endLandBuild();
    this->endFly();
    this->endFlyEffect();
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
    item_magnetCurrentTime = item_magnetLastTime;
//    if (!item_magnetIcon)
//    {
//        item_magnetIcon = Sprite::createWithSpriteFrameName("item_mag.png");
//        item_magnetIcon->setPosition(this->getIconPosition());
//        this->addChild(item_magnetIcon);
//    }
    m_gameController->addPowerIcon(PowerIcon::PowerType::MAGNET);
}

void Runner::endMagnet()
{
    if (!this->isMagnetING())
    {
        return;
    }
    if (!this->isFlyING())
    {
        this->setMagnetING(false);
    }
//    if (item_magnetIcon)
//    {
//        item_magnetIcon->removeFromParentAndCleanup(true);
//        item_magnetIcon = nullptr;
//        
//    }
    m_gameController->removePowerIcon(PowerIcon::PowerType::MAGNET);
}

void Runner::startTimesCoin()
{
    this->setTimesCoinING(true);
    item_timesCoinCurrentTime = item_timesCoinLastTime;
    
//    if (!item_timesCoinIcon)
//    {
//        item_timesCoinIcon = Sprite::createWithSpriteFrameName("item_timecoin.png");
//        item_timesCoinIcon->setPosition(this->getIconPosition());
//        this->addChild(item_timesCoinIcon);
//    }
    m_gameController->addPowerIcon(PowerIcon::PowerType::TIMESCOIN);
}
void Runner::endTimesCoin()
{
    if (!this->isTimesCoinING())
    {
        return;
    }
    this->setTimesCoinING(false);
//    
//    if (item_timesCoinIcon)
//    {
//        item_timesCoinIcon->removeFromParentAndCleanup(true);
//        item_timesCoinIcon = nullptr;
//    }
    m_gameController->removePowerIcon(PowerIcon::PowerType::TIMESCOIN);
}

void Runner::startTimesJump()
{
    this->setTimesJumpING(true);
    item_timesJumpCurrentTime = item_timesJumpLastTime;
    
//    if (!item_timesJumpIcon)
//    {
//        item_timesJumpIcon = Sprite::createWithSpriteFrameName("item_jump.png");
//        item_timesJumpIcon->setPosition(this->getIconPosition());
//        this->addChild(item_timesJumpIcon);
//    }
    m_gameController->addPowerIcon(PowerIcon::PowerType::TIMESJUMP);
}
void Runner::endTimesJump()
{
    if (!this->isTimesJumpING())
    {
        return;
    }
    this->setTimesJumpING(false);
    
//    if (item_timesJumpIcon)
//    {
//        item_timesJumpIcon->removeFromParentAndCleanup(true);
//        item_timesJumpIcon = nullptr;
//    }
    m_gameController->removePowerIcon(PowerIcon::PowerType::TIMESJUMP);
}

void Runner::startDad()
{
    this->setDadING(true);
    item_dadCurrentTime = item_dadLastTime;
    
//    if (!item_dadIcon)
//    {
//        item_dadIcon = Sprite::createWithSpriteFrameName("item_dad.png");
//        item_dadIcon->setPosition(this->getIconPosition());
//        this->addChild(item_dadIcon);
//    }
    m_gameController->addPowerIcon(PowerIcon::PowerType::DAD);
}
void Runner::endDad()
{
    if (!this->isDadING())
    {
        return;
    }
    this->setDadING(false);
    
//    if (item_dadIcon)
//    {
//        item_dadIcon->removeFromParentAndCleanup(true);
//        item_dadIcon = nullptr;
//    }
    m_gameController->removePowerIcon(PowerIcon::PowerType::DAD);
}

void Runner::startLandBuild()
{
    this->setLandBuildING(true);
    item_buildLandCurrentTime = item_buildLandLastTime;
    
//    if (!item_buildLandIcon)
//    {
//        item_buildLandIcon = Sprite::createWithSpriteFrameName("item_buildland.png");
//        item_buildLandIcon->setPosition(this->getIconPosition());
//        this->addChild(item_buildLandIcon);
//    }
    m_gameController->addPowerIcon(PowerIcon::PowerType::LANDBUILD);
}
void Runner::endLandBuild()
{
    if (!this->isLandBuildING())
    {
        return;
    }
    if (!this->isFlyING())
    {
        this->setLandBuildING(false);
    }
    
//    if (item_buildLandIcon)
//    {
//        item_buildLandIcon->removeFromParentAndCleanup(true);
//        item_buildLandIcon = nullptr;
//    }
    m_gameController->removePowerIcon(PowerIcon::PowerType::LANDBUILD);
}

void Runner::startFly()
{
    if (this->isFlyING())
    {
        m_gameController->endFly();
    }
    item_flyCurrentTime = item_flyLastTime;
    
    item_isEndFlyING = false;
    
    m_gameController->startFly();
    
    this->setFlyING(true);
    this->setGravityEffect(false);
    this->setYA(0.0f);
    this->setYV(0.0f);
    this->setXA(0.0f);
    this->setXV(0.0f);
    this->setDad(true);
    this->setIgnoreLand(true);
    this->setRunnerState(kRunnerState_JumpUp);
    this->setMagnetING(true);
    
//    m_gameController->setVelocity(3600);
    
//    if (!item_flyIcon)
//    {
//        item_flyIcon = Sprite::createWithSpriteFrameName("item_fly.png");
//        item_flyIcon->setPosition(this->getIconPosition());
//        this->addChild(item_flyIcon);
//    }
    m_gameController->addPowerIcon(PowerIcon::PowerType::FLY);
}
void Runner::endFly()
{
    if (!this->isFlyING())
    {
        return;
    }
    if (item_isEndFlyING)
    {
        return;
    }
    
    item_isEndFlyING = true;
    this->setGravityEffect(true);
    this->setIgnoreLand(false);
    if (item_magnetCurrentTime <= 0)
    {
        this->setMagnetING(false);
    }
    this->setLandBuildING(true);
    
//    m_gameController->setVelocity(400);
    m_gameController->endFly();
}
void Runner::endFlyEffect()
{
    item_isEndFlyING = false;
    this->setFlyING(false);
    
    if (item_dadCurrentTime <= 0)
    {
        this->setDad(false);
    }
    if (item_buildLandCurrentTime <= 0)
    {
        this->setLandBuildING(false);
    }
    
//    if (item_flyIcon)
//    {
//        item_flyIcon->removeFromParentAndCleanup(true);
//        item_flyIcon = nullptr;
//    }
    
    m_gameController->removePowerIcon(PowerIcon::PowerType::FLY);
}

void Runner::startReborn()
{
    this->setRebornING(true);
    item_rebornCurrentTime = item_rebornLastTime;
    
    m_gameController->addPowerIcon(PowerIcon::PowerType::REBORN);
}
void Runner::endReborn()
{
    this->setRebornING(false);
    m_gameController->removePowerIcon(PowerIcon::PowerType::REBORN);
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