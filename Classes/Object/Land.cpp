//
//  Land.cpp
//  CoolRun
//
//  Created by ManYou on 14/12/29.
//
//

#include "Land.h"


Land::Land()
: PhysicNode()
, m_isLand(false)
, m_isLeftIgnore(false)
, m_isRightIgnore(false)
, m_isUpIgnore(false)
, m_isDownIgnore(false)
{
}
Land::~Land()
{
}
bool Land::init()
{
    if (!PhysicNode::init())
    {
        return false;
    }
    
    
    return true;
}

void Land::onEnter()
{
    PhysicNode::onEnter();
    
    auto  pos = this->getPosition();
    
    if (pos.y < 10.0f)
    {
        this->setLand(true);
    }
}
void Land::onExit()
{
    PhysicNode::onExit();
}

void Land::showTips(int index)
{
    stringstream ss;
    ss << index;
    
    Label* label = dynamic_cast<Label*>(this->getChildByTag(999));
    
    if (!label)
    {
        auto _label = Label::createWithTTF(ss.str(), "Marker Felt.ttf", 32);
        _label->setPosition(Vec2(0, 0));
        this->addChild(_label, 10);
        _label->setTag(999);

    }
    else
    {
        label->setString(ss.str());
    }
    
}
