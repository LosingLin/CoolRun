//
//  SpiderSpines.cpp
//  CoolRun
//
//  Created by ManYou on 14/11/26.
//
//

#include "SpiderSpines.h"
#include "Runner.h"
#include "Bullet.h"

SpiderSpines::SpiderSpines()
: Spider()
{
}
SpiderSpines::~SpiderSpines()
{
}
bool SpiderSpines::init()
{
    if (!Spider::init())
    {
        return false;
    }
    
    m_armature = Armature::create("SpiderSpine");
    m_armature->setScale(0.8f);
    this->addChild(m_armature);
    
    auto csize = m_armature->getContentSize() * 0.8f;
    this->setContentSize(csize);
    
    m_armature->setPosition(Vec2(csize.width / 2, csize.height / 2));
    
    this->setCollideRect(Rect(40, 44, csize.width * 0.8f, csize.height - 60));
    
    this->debugShow();
    
    return true;
}

void SpiderSpines::setState(SpiderState state)
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
    m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(SpiderSpines::movementEvent, this));
    m_armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_4(SpiderSpines::frameEvent, this));
}

void SpiderSpines::dead()
{
    this->setState(kSpiderState_Hurted);
    this->setCollideEffect(false);
}

#pragma mark - bone callback
void SpiderSpines::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (MovementEventType::COMPLETE == movementType)
    {
        if("hurt" == movementID)
        {
            this->setDestoryed(true);
        }
        
    }
}
void SpiderSpines::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
}

#pragma mark - collide

void SpiderSpines::trackCollideWithRunner(Runner* _runner)
{
    Spider::trackCollideWithRunner(_runner);
    
    if (!this->isCollideEffect() || this->isDestoryed())
    {
        return;
    }
    
    auto rect1 = PhysicHelp::countPhysicNodeRect(this);
    if (_runner->isAtk())
    {
        auto rect2 = PhysicHelp::countPhysicNodeRect(_runner, _runner->getAtkRect());
        
        bool isAtked = CollideTrackHelp::trackCollide(rect1, rect2);
        if (isAtked)
        {
            this->dead();
            return;
        }
        
    }
    
    auto rect2 = PhysicHelp::countPhysicNodeRect(_runner);
    bool isKilled = CollideTrackHelp::trackCollide(rect1, rect2);
    if (isKilled)
    {
        m_gameController->dead(_runner);
//        this->setCollideEffect(false);
    }
}

void SpiderSpines::trackCollideWithBullet(Bullet* bullet)
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

