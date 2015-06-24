//
//  Background.cpp
//  CoolRun
//
//  Created by ManYou on 14/10/21.
//
//

#include "Background.h"
#include "Base.h"


Background::Background()
: Layer()
, m_bgs(nullptr)
, m_velocity(0.0f)
, m_index(0)
{
}
Background::~Background()
{
    CC_SAFE_RELEASE_NULL(m_bgs);
}
bool Background::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    CREATEANDRETAINARRAY(m_bgs);
    
    return true;
}

void Background::addBackgound(const std::string& framename)
{
    
    float scale = 1274.0f/1000.0f;
    
    auto _sp = Sprite::createWithSpriteFrameName(framename);
    _sp->setAnchorPoint(Vec2(0, 0));
    _sp->setScale(scale, scale);
    _sp->setPosition(Vec2(m_index*1264.0f, 0));
    //_sp->setPosition(Vec2(m_index*1024.0f, 0));
    this->addChild(_sp);
    
    m_index++;
    
    m_bgs->addObject(_sp);
}

Sprite* Background::getMaxPositionSprite()
{
    Sprite* maxSp = nullptr;
    
    for (int i = 0; i < m_bgs->count(); ++ i)
    {
        auto _sp = dynamic_cast<Sprite*>(m_bgs->getObjectAtIndex(i));
        auto pos = _sp->getPosition();
        if (maxSp == nullptr)
        {
            maxSp = _sp;
        }
        else
        {
            auto maxPos = maxSp->getPosition();
            if (pos.x > maxPos.x)
            {
                maxSp = _sp;
            }
        }
    }
    
    return maxSp;
}

void Background::updateBackGround(float delta)
{
    
    for (int i = 0; i < m_bgs->count(); ++ i)
    {
        auto _sp = dynamic_cast<Sprite*>(m_bgs->getObjectAtIndex(i));
        auto pos = _sp->getPosition();
        pos.x -= m_velocity * delta;
        if (pos.x < -1264.0f)
        {
            auto _lastSp = getMaxPositionSprite();
            auto _lastPos = _lastSp->getPosition();
            _lastPos.x -= m_velocity * delta;
            pos.x = _lastPos.x + 1264.0f;
            
            //log("lastPos.x : %f, pos.x : %f", _lastPos.x, pos.x);
        };
        _sp->setPosition(pos);
    }
}


Background* Background::create(const std::string& framename01, const std::string& framename02)
{
    auto _bg = Background::create();
    _bg->addBackgound(framename01);
    _bg->addBackgound(framename02);
    return _bg;
}