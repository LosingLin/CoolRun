//
//  Boss.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/15.
//
//

#include "Boss.h"

Boss::Boss()
: Animal()
, m_armature(nullptr)
, b_isReady(false)
, b_isAtking(false)
, m_atkIndex(0)
{
    
}
Boss::~Boss()
{
    
}

bool Boss::init()
{
    if (!Animal::init())
    {
        return false;
    }
    
    return true;
}