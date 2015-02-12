//
//  CollideNode.cpp
//  CoolRun
//
//  Created by ManYou on 14-9-9.
//
//

#include "CollideNode.h"

CollideNode::CollideNode()
: PhysicNode()
, m_gameController(nullptr)
{
}
CollideNode::~CollideNode()
{
}

bool CollideNode::init()
{
    if (!PhysicNode::init())
    {
        return false;
    }
    
    return true;
}