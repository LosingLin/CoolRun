//
//  Enemy.cpp
//  CoolRun
//
//  Created by ManYou on 14-9-9.
//
//

#include "Enemy.h"
#include "PhysicHelp.h"
#include "Runner.h"

Enemy::Enemy()
: Animal()
, m_armature(nullptr)
, b_isAtk(false)
{
}
Enemy::~Enemy()
{
}
bool Enemy::init()
{
    if (!Animal::init())
    {
        return false;
    }
    
    m_armature = Armature::create("Spider");
    m_armature->setScale(0.8f);
    this->addChild(m_armature);
    
    auto csize = m_armature->getContentSize() * 0.8f;
    this->setContentSize(csize);
    
    this->setCollideRect(Rect(20, 40, csize.width * 0.8f, csize.height * 0.8));
    
    m_armature->setPosition(Vec2(csize.width / 2, csize.height / 2));
    
    m_armature->getAnimation()->play("walk03");
    
    this->debugShow();
    
    return true;
}

Enemy* Enemy::create(rapidjson::Value& _value)
{
    auto _emy = Enemy::create();
    _emy->loadJson(_value);
    _emy->debugShow();
    return _emy;
}

#pragma mark - bone callback

void Enemy::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    log("movementID : %s", movementID.c_str());
    
    if (MovementEventType::COMPLETE == movementType)
    {
        if ("attack" == movementID)
        {
            m_armature->getAnimation()->play("walk03");
        }
        else if("hurt03" == movementID)
        {
            this->setDestoryed(true);
        }
        
    }
    
}
void Enemy::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
}


#pragma mark - collide

void Enemy::trackCollideWithRunner(Runner* _runner)
{
    //处理near的逻辑 和 攻击的逻辑
    auto rect1 = PhysicHelp::countPhysicNodeRect(this, this->getMultiRect(0));
    auto rect2 = PhysicHelp::countPhysicNodeRect(_runner);
    if (!b_isAtk)
    {
        auto isNear = CollideTrackHelp::isNearRight(rect2, rect1, 50.0f);
        if (isNear)
        {
            b_isAtk = true;
            
            m_armature->getAnimation()->play("attack", -1, 1);
            m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(Enemy::movementEvent, this));
            
            //m_gameController->pause();
        }
    }
    
    auto isKill = CollideTrackHelp::trackCollide(rect1, rect2);
    if (isKill)
    {
//        m_armature->getAnimation()->play("hurt", -1, 1);
//        m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(Enemy::movementEvent, this));
//        this->setCollideEffect(false);
        
//        m_gameController->pause();
        return;
    }
    
    //处理跳踩
    rect1 = PhysicHelp::countPhysicNodeRect(this, this->getMultiRect(1));
    
    
    auto isCollide = CollideTrackHelp::trackCollide(rect1, rect2);
    if (isCollide)
    {
        _runner->setJumpCount(0);
        _runner->jump();
        
        m_armature->getAnimation()->play("hurt03");
        m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(Enemy::movementEvent, this));
        this->setCollideEffect(false);
    }
    
    
}

void Enemy::CollideTrackListener_CollideOnce(CollideDirection direction, PhysicNode *node)
{
    
    auto rect1 = PhysicHelp::countPhysicNodeRect(node);
    auto rect2 = PhysicHelp::countPhysicNodeRect(this);
    
    if (direction == kCollideDirectionUp) {

        auto dis = rect1.size.height - rect2.origin.y + rect1.origin.y;
        auto pos = this->getPosition();
        pos.y += (dis-1);
        //        if (pos.y < (pos.y + dis)) {
        //            pos.y += (dis/2 - 1);
        //        }
        this->setPosition(pos);
        
        this->setYA(0.0f);
        this->setYV(0.0f);
        
        PhysicHelp::showTips("Up", this, Vec2(0, 0));
        
    }
    else if(direction == kCollideDirectionLeft) {
        PhysicHelp::showTips("Left", this, Vec2(0, 0));
        
//        auto dis = rect2.size.width - rect1.origin.x + rect2.origin.x;
//        
//        auto pos = this->getPosition();
//        pos.x -= dis;
//        this->setPosition(pos);

//        this->setXV(node->getXV());
//        this->setXA(node->getXA());
    }
    else if(direction == kCollideDirectionDown)
    {
        PhysicHelp::showTips("Down", this, Vec2(0, 0));
        
        auto dis = rect1.size.height - rect2.origin.y + rect1.origin.y;
        auto pos = this->getPosition();
        //pos.y -= dis;
        if (pos.y > (pos.y - dis)) {
            pos.y --;
        }
        this->setPosition(pos);
        
//        this->setYA(0.0f);
//        this->setYV(0.0f);
    }
}
void Enemy::CollideTrackListener_CollideAll(CollideDirection direction)
{
    if (direction == kCollideDirectionMiss) {
        
//        this->setXA(0.0f);
//        this->setXV(0.0f);
        
    }
}