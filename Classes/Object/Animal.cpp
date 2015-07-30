//
//  Animal.cpp
//  CoolRun
//
//  Created by ManYou on 14/11/26.
//
//

#include "Animal.h"

Animal::Animal()
: MultipleCollideNode()
, m_score(0)
{
}
Animal::~Animal()
{
}
bool Animal::init()
{
    if (!MultipleCollideNode::init())
    {
        return false;
    }
    
    this->setLocalZOrder(ZORDER_ANIMAL);
    
    return true;
}

void Animal::dead()
{
    this->addPlayerScore();
}

void Animal::addPlayerScore()
{
    auto score = this->getScore();
    m_gameController->addScore(score);
}

void Animal::CollideTrackListener_CollideOnce(CollideDirection direction, PhysicNode *node)
{
    
    auto rect1 = PhysicHelp::countPhysicNodeRect(node);
    auto rect2 = PhysicHelp::countPhysicNodeRect(this);
    
    if (direction == kCollideDirectionUp) {
        
        auto dis = rect1.size.height - rect2.origin.y + rect1.origin.y;
        auto pos = this->getPosition();
        pos.y += (dis-1);
        
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
//        
//        this->setXV(node->getXV());
//        this->setXA(node->getXA());
    }
    else if(direction == kCollideDirectionDown)
    {
        PhysicHelp::showTips("Down", this, Vec2(0, 0));
        
        auto dis = rect1.size.height - rect2.origin.y + rect1.origin.y;
        auto pos = this->getPosition();
        if (pos.y > (pos.y - dis)) {
            pos.y --;
        }
        this->setPosition(pos);
        
    }
    else if (direction == kCollideDirectionRight)
    {
        PhysicHelp::showTips("Right", this, Vec2(0, 0));
        auto dis = rect2.size.width - rect1.origin.x + rect2.origin.x;
        
        auto pos = this->getPosition();
        pos.x -= dis;
        this->setPosition(pos);
        
        this->setXV(node->getXV());
        this->setXA(node->getXA());
    }
}
void Animal::CollideTrackListener_CollideAll(CollideDirection direction)
{
    if (direction == kCollideDirectionMiss) {
        
        //        this->setXA(0.0f);
        //        this->setXV(0.0f);
        
    }
}