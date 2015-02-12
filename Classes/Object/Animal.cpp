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
}
void Animal::CollideTrackListener_CollideAll(CollideDirection direction)
{
    if (direction == kCollideDirectionMiss) {
        
        //        this->setXA(0.0f);
        //        this->setXV(0.0f);
        
    }
}