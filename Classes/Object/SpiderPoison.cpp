//
//  SpiderPoison.cpp
//  CoolRun
//
//  Created by ManYou on 14/11/26.
//
//

#include "SpiderPoison.h"
#include "PoisonBullet.h"
#include "Runner.h"
#include "Bullet.h"

SpiderPoison::SpiderPoison()
: Spider()
, b_isAtking(false)
, m_atkDirection(kCRDirectionUp)
{
}
SpiderPoison::~SpiderPoison()
{
}
bool SpiderPoison::init()
{
    if (!Spider::init())
    {
        return false;
    }
    
    auto csize = this->getContentSize();
    
    this->setCollideRect(Rect(40, 20, csize.width * 0.8f, csize.height * 0.8));
    
    this->debugShow();
    
    return true;
}

void SpiderPoison::setState(SpiderState state)
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
    m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(SpiderPoison::movementEvent, this));
    m_armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_4(SpiderPoison::frameEvent, this));
}

void SpiderPoison::dead()
{
    this->setState(kSpiderState_Hurted);
    this->setCollideEffect(false);
}

void SpiderPoison::attack()
{
    b_isAtking = true;
    auto v = m_gameController->getVelocity();
    this->setXV(-v);
    
    auto bullet = PoisonBullet::create();
    bullet->setAtkDirection(m_atkDirection);
    auto pos = this->getPosition();
    
    switch (m_atkDirection)
    {
        case kCRDirectionUp:
        {
            bullet->setXV(-v);
            bullet->setYV(600);
            bullet->setPosition(Vec2(pos.x + 100, pos.y + 60));
            m_gameController->addBullet(bullet);
        }
            break;
        case kCRDirectionDown:
        {
            m_gameController->addBullet(bullet);
        }
            break;
        case kCRDirectionLeft:
        {
            bullet->setXV(-v-600);
            bullet->setPosition(Vec2(pos.x + 100, pos.y + 60));
            m_gameController->addBullet(bullet);
        }
            break;
        case kCRDirectionRight:
        {
            bullet->setXV(v+600);
            bullet->setPosition(Vec2(pos.x + 100, pos.y + 60));
            m_gameController->addBullet(bullet);
        }
            break;
        default:
            break;
    }
    
}

void SpiderPoison::attackDone()
{
    this->setDestoryed(true);
}

void SpiderPoison::setAtkDirection(CRDirection direction)
{
    m_atkDirection = direction;
    Bone* bellyNormal = m_armature->getBone("belly_normal");
    Bone* bellyHurted = m_armature->getBone("belly_hurted");
//    switch (m_atkDirection)
//    {
//        case kCRDirectionRight:
//        {
//            bellyNormal->setPosition(Vec2(-40, -120));
//            bellyNormal->setRotation(96);
//            bellyHurted->setRotation(98);
//        }
//            break;
//            
//        default:
//            break;
//    }
    
}

#pragma mark - bone callback
void SpiderPoison::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (MovementEventType::COMPLETE == movementType)
    {
        if("hurt" == movementID)
        {
            this->attack();
            this->setDestoryed(true);
        }
        
    }
}
void SpiderPoison::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
}

#pragma mark - collide

void SpiderPoison::trackCollideWithRunner(Runner* _runner)
{
    Spider::trackCollideWithRunner(_runner);
    
    if (!this->isCollideEffect() || this->isDestoryed())
    {
        return;
    }
    
    //处理与玩家的碰撞
    if (!b_isAtking)
    {
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
        
        CollideDirection dir = CollideTrackHelp::trackCollideDirection(rect1, rect2);
        
        if (kCollideDirectionUp == dir)
        {
            _runner->rebound();
            
            this->dead();
        }
        else if (kCollideDirectionMiss != dir)
        {
            m_gameController->dead(_runner);
            
//            this->setCollideEffect(false);
        }
    }
    else
    {
//        CCASSERT(m_bullet, "m_bullet can't be null");
//        auto bulletPos = m_bullet->getPosition();
//        auto bulletSize = m_bullet->getContentSize();
//        auto bulletRect = Rect(bulletPos.x - bulletSize.width/2, bulletPos.y - bulletSize.height/2, bulletSize.width, bulletSize.height);
//        
//        auto rect1 = PhysicHelp::countPhysicNodeRect(this, bulletRect);
//        auto rect2 = PhysicHelp::countPhysicNodeRect(_runner);
//        
//        bool isAtked = CollideTrackHelp::trackCollide(rect1, rect2);
//        if (isAtked)
//        {
//            
//            m_gameController->dead(_runner);
//            
//            this->setDestoryed(true);
//            
//            //SHOW_RECT(bulletRect);
//        }
    }
}

void SpiderPoison::trackCollideWithBullet(Bullet* bullet)
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