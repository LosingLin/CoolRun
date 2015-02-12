//
//  CollideRect.cpp
//  CoolRun
//
//  Created by ManYou on 14/10/27.
//
//

#include "CollideRect.h"

CollideRect::CollideRect()
: Ref()
, m_id(-1)
, m_rect(Rect(0, 0, 0, 0))
{
}
CollideRect::~CollideRect()
{
}
bool CollideRect::init()
{
    return true;
}



CollideRect* CollideRect::create(const Rect& _rect, int _id)
{
    auto collideRect = CollideRect::create();
    collideRect->setRect(_rect);
    collideRect->setId(_id);
    
    return collideRect;
}