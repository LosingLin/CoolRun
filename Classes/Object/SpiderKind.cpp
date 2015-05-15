//
//  SpiderKind.cpp
//  CoolRun
//
//  Created by ManYou on 14/11/26.
//
//

#include "SpiderKind.h"
#include "Runner.h"
#include "Bullet.h"


SpiderKind::SpiderKind()
: Spider()
{
}
SpiderKind::~SpiderKind()
{
}
bool SpiderKind::init()
{
    if (!Spider::init())
    {
        return false;
    }
    
    m_armature = Armature::create("SpiderKind");
    m_armature->setScale(0.8f);
    this->addChild(m_armature);
    
    auto csize = m_armature->getContentSize() * 0.8f;
    this->setContentSize(csize);
    
    m_armature->setPosition(Vec2(csize.width / 2, csize.height / 2));
    
    this->setCollideRect(Rect(40, 44, csize.width * 0.8f, csize.height - 80));
    
    this->addRect(Rect(46, 50, 40, 80)); //头部
    this->addRect(Rect(90, 50, 130, 100)); //尾部
    
    this->debugShow();
    
    this->setScore(2);
    
    return true;
}

void SpiderKind::setState(SpiderState state)
{
    Spider::setState(state);
    switch (m_state) {
        case kSpiderState_Attack:
            m_armature->getAnimation()->play("attack");
            break;
        case kSpiderState_Stand:
            m_armature->getAnimation()->play("stand");
            break;
        case kSpiderState_Hurted:
            m_armature->getAnimation()->play("hurt");
            break;
        case kSpiderState_Walk:
            m_armature->getAnimation()->play("walk");
            break;
        default:
            break;
    }
    m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(SpiderKind::movementEvent, this));
    m_armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_4(SpiderKind::frameEvent, this));
}

void SpiderKind::dead()
{
    Spider::dead();
    this->setState(kSpiderState_Hurted);
    this->setCollideEffect(false);
}

#pragma mark - bone callback
void SpiderKind::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (MovementEventType::COMPLETE == movementType)
    {
        if("hurt" == movementID)
        {
            this->setDestoryed(true);
        }
        
    }
}
void SpiderKind::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
}

#pragma mark - collide

void SpiderKind::trackCollideWithRunner(Runner* _runner)
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
    
    if (_runner->isAtk())
    {
        auto rect2 = PhysicHelp::countPhysicNodeRect(_runner, _runner->getAtkRect());
        
        bool isAtked = CollideTrackHelp::trackCollide(rect1, rect2);
        if (isAtked)
        {
            AudioHelp::playBeAttackedEft();
            
            this->dead();
            return;
        }
        
    }
    
    auto rect2 = PhysicHelp::countPhysicNodeRect(_runner);
    
    if (_runner->isCollidedWithTrueBody(headRect))
    {
        m_gameController->dead(_runner);
        return;
    }
    
    CollideDirection dir = _runner->getDirectionWithTrueBody(tailRect);
    
    if (kCollideDirectionUp == dir)
    {
        _runner->rebound();
        
        this->dead();
    }
    else if (kCollideDirectionMiss != dir)
    {
        m_gameController->dead(_runner);
        
//        this->setCollideEffect(false);
    }
}

void SpiderKind::trackCollideWithBullet(Bullet* bullet)
{
    auto rect1 = PhysicHelp::countPhysicNodeRect(bullet);
    auto rect2 = PhysicHelp::countPhysicNodeRect(this);
    
    bool isCollided = CollideTrackHelp::trackCollide(rect1, rect2);
    if (isCollided)
    {
        AudioHelp::playBeAttackedEft();
        
        this->dead();
        bullet->setDestoryed(true);
    }
}


