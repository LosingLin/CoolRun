//
//  SpiderFly.cpp
//  CoolRun
//
//  Created by ManYou on 15/3/4.
//
//

#include "SpiderFly.h"
#include "Runner.h"
#include "Bullet.h"


SpiderFly::SpiderFly()
: Spider()
{
}
SpiderFly::~SpiderFly()
{
}
bool SpiderFly::init()
{
    if (!Spider::init())
    {
        return false;
    }
    
    m_armature = Armature::create("SpiderFly");
    m_armature->setScale(0.8f);
    this->addChild(m_armature);
    
    auto csize = m_armature->getContentSize() * 0.8f;
    this->setContentSize(csize);
    
    m_armature->setPosition(Vec2(csize.width / 2, csize.height / 2));
    
    this->setCollideRect(Rect(50, 20, csize.width * 0.8f, csize.height * 0.6));
    
    this->addRect(Rect(54, 70, 50, 40)); //头部
    this->addRect(Rect(100, 60, 120, 70)); //尾部
    this->addRect(Rect(90, 10, 100, 60)); //腿部
    
    this->debugShow();
    
    this->setGravityEffect(false);
    
    this->setScore(4);
    
    return true;
}

void SpiderFly::setState(SpiderState state)
{
    Spider::setState(state);
    switch (m_state) {
        case kSpiderState_Attack:
            m_armature->getAnimation()->play("stand");
            break;
        case kSpiderState_Stand:
            m_armature->getAnimation()->play("stand");
            break;
        case kSpiderState_Hurted:
            m_armature->getAnimation()->play("hurt");
            break;
        case kSpiderState_Walk:
            m_armature->getAnimation()->play("stand");
            break;
        default:
            break;
    }
    m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(SpiderFly::movementEvent, this));
    m_armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_4(SpiderFly::frameEvent, this));
}

void SpiderFly::dead()
{
    Spider::dead();
    this->setState(kSpiderState_Hurted);
    this->setCollideEffect(false);
    this->setGravityEffect(true);
}

#pragma mark - bone callback
void SpiderFly::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (MovementEventType::COMPLETE == movementType)
    {
        if("hurt" == movementID)
        {
            this->setGravityEffect(true);
        }
        
    }
}
void SpiderFly::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
}

#pragma mark - collide

void SpiderFly::trackCollideWithRunner(Runner* _runner)
{
    
    Spider::trackCollideWithRunner(_runner);
    if (!this->isCollideEffect() || this->isDestoryed())
    {
        return;
    }
    //处理与玩家的碰撞
    auto rect1 = PhysicHelp::countPhysicNodeRect(this);
    
    auto headRect = PhysicHelp::countPhysicNodeRect(this, this->getMultiRect(0));
    auto tailRect = PhysicHelp::countPhysicNodeRect(this, this->getMultiRect(1));
    auto legRect = PhysicHelp::countPhysicNodeRect(this, this->getMultiRect(2));
    
    if (_runner->isAtk())
    {
        auto rect2 = PhysicHelp::countPhysicNodeRect(_runner, _runner->getAtkRect());
        
        bool isAtked01 = CollideTrackHelp::trackCollide(headRect, rect2);
        bool isAtked02 = CollideTrackHelp::trackCollide(tailRect, rect2);
        bool isAtked03 = CollideTrackHelp::trackCollide(legRect, rect2);
        if (isAtked01 || isAtked02 || isAtked03)
        {
            this->dead();
            return;
        }
        
    }
    
    auto rect2 = PhysicHelp::countPhysicNodeRect(_runner);
    
    if (CollideTrackHelp::trackCollide(headRect, rect2) || CollideTrackHelp::trackCollide(legRect, rect2))
    {
        m_gameController->dead(_runner);
        
        return;
    }
    
    CollideDirection dir = CollideTrackHelp::trackCollideDirection(tailRect, rect2);
    
    if (kCollideDirectionUp == dir)
    {
        _runner->rebound();
        this->setYV(100);
        this->dead();
    }
    else if (kCollideDirectionMiss != dir && kCollideDirectionRight != dir)
    {
        m_gameController->dead(_runner);
        
        //        this->setCollideEffect(false);
    }
}

void SpiderFly::trackCollideWithBullet(Bullet* bullet)
{
    auto rect1 = PhysicHelp::countPhysicNodeRect(bullet);
    auto rect2 = PhysicHelp::countPhysicNodeRect(this);
    
    bool isCollided = CollideTrackHelp::trackCollide(rect1, rect2);
    if (isCollided)
    {
        this->dead();
        bullet->setDestoryed(true);
    }
}