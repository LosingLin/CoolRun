//
//  MultipleCollideNode.cpp
//  CoolRun
//
//  Created by ManYou on 14/10/27.
//
//

#include "MultipleCollideNode.h"
#include "Base.h"
#include "CollideRect.h"

MultipleCollideNode::MultipleCollideNode()
: CollideNode()
, m_rectIndex(0)
, m_multiRects(nullptr)
{
}
MultipleCollideNode::~MultipleCollideNode()
{
    CC_SAFE_RELEASE_NULL(m_multiRects);
}

bool MultipleCollideNode::init()
{
    if (!CollideNode::init())
    {
        return false;
    }
    
    CREATEANDRETAINARRAY(m_multiRects);
    
    return true;
}

void MultipleCollideNode::loadJson(rapidjson::Value& _value)
{
    PhysicNode::loadJson(_value);
    
    if (_value.HasMember("multiRects"))
    {
        rapidjson::Value& _rects = _value["multiRects"];
        
        if (_rects.IsArray())
        {
            for (int i = 0; i < _rects.Size(); ++i)
            {
                Rect rect;
                JsonHelp::buildRect(_rects[i], rect);
                auto _cRect = CollideRect::create(rect, m_rectIndex++);
                m_multiRects->addObject(_cRect);
                
                SHOW_RECT(rect);
            }
        }
    }
}

const Rect MultipleCollideNode::getMultiRect(int id)
{
    for (int i = 0; i < m_multiRects->count(); ++ i)
    {
        auto _cRect = dynamic_cast<CollideRect*>(m_multiRects->getObjectAtIndex(i));
        if (id == _cRect->getId())
        {
            return _cRect->getRect();
        }
    }
    
    return Rect(0, 0, 0, 0);
}

void MultipleCollideNode::addRect(const Rect& rect)
{
    auto _cRect = CollideRect::create(rect, m_rectIndex++);
    m_multiRects->addObject(_cRect);
    
    SHOW_RECT(rect);
}