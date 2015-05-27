//
//  Spider.cpp
//  CoolRun
//
//  Created by ManYou on 14/11/26.
//
//

#include "Spider.h"
#include "PhysicHelp.h"
#include "Runner.h"

Spider::Spider()
: Animal()
, m_armature(nullptr)
, m_state(kSpiderState_Unknown)
{
}
Spider::~Spider()
{
}
bool Spider::init()
{
    if (!Animal::init())
    {
        return false;
    }
    this->setCollideType(CollideType::kCollideTypeSimple);
    
    this->setGravityEffect(true);
    this->setCollideEffect(true);
    
    return true;
}

Spider* Spider::create(rapidjson::Value& _value)
{
    auto _emy = Spider::create();
    _emy->loadJson(_value);
    _emy->debugShow();
    return _emy;
}

void Spider::setState(SpiderState state)
{
    if (m_state == state)
    {
        return;
    }
    
    m_state = state;
}

void Spider::loadJson(rapidjson::Value& _value)
{
    Animal::loadJson(_value);
    
    //默认是站着的状态
    SpiderState state = kSpiderState_Stand;
    
    if (_value.HasMember("state")) {
        state = (SpiderState)JsonHelp::getInt(_value["state"]);
    }
    this->setState(state);
}

void Spider::saveData(string* buffer)
{
    Animal::saveData(buffer);
    
    string str = string();
    stringstream ss;
    ss << "\"state\":";
    ss << this->getState();
    ss << ",";
    ss >> str;
    buffer->append(str);
}

#pragma mark - bone callback

void Spider::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{

    
}
void Spider::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
}


#pragma mark - collide

void Spider::trackCollideWithRunner(Runner* _runner)
{
    if (_runner->isDad() || _runner->isRebornING())
    {
        auto rect1 = PhysicHelp::countPhysicNodeRect(_runner);
        auto rect2 = PhysicHelp::countPhysicNodeRect(this);
        
        auto isCollide = CollideTrackHelp::trackCollide(rect1, rect2);
        if (isCollide)
        {
            this->dead();
            return;
        }
    }
    
    
}

void Spider::CollideTrackListener_CollideOnce(CollideDirection direction, PhysicNode *node)
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
void Spider::CollideTrackListener_CollideAll(CollideDirection direction)
{
    if (direction == kCollideDirectionMiss) {
        
        //        this->setXA(0.0f);
        //        this->setXV(0.0f);
        
    }
}

void Spider::trackCollideWithBullet(Bullet* bullet)
{
}