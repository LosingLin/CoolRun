//
//  PowerIcon.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/22.
//
//

#include "PowerIcon.h"


PowerIcon::PowerIcon()
: Node()
, m_icon(nullptr)
, m_proBg(nullptr)
{
    
}
PowerIcon::~PowerIcon()
{
    
}

bool PowerIcon::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    
    return true;
}

bool PowerIcon::init(PowerType _type)
{
    if (!this->init())
    {
        return false;
    }
    
    auto bg = Sprite::createWithSpriteFrameName("power_proBG.png");
    auto csize = bg->getContentSize();
    this->setContentSize(csize);
    bg->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(bg);
    
    auto pro = Sprite::createWithSpriteFrameName("power_pro.png");
    m_proBg = ProgressTimer::create(pro);
    m_proBg->setType(ProgressTimer::Type::RADIAL);
    m_proBg->setReverseProgress(true);
    m_proBg->setAnchorPoint(Vec2(0.5, 0.5));
    m_proBg->setPosition(Vec2(csize.width/2, csize.height/2));
    m_proBg->setPercentage(100);
    this->addChild(m_proBg);
    
    this->setPowerType(_type);
    switch (_type)
    {
        case PowerType::SPARE:
        {
            m_icon = Sprite::createWithSpriteFrameName("item_spare.png");
        }
            break;
        case PowerType::MAGNET:
        {
            m_icon = Sprite::createWithSpriteFrameName("item_mag.png");
        }
            break;
        case PowerType::TIMESCOIN:
        {
            m_icon = Sprite::createWithSpriteFrameName("item_timecoin.png");
        }
            break;
        case PowerType::TIMESJUMP:
        {
            m_icon = Sprite::createWithSpriteFrameName("item_jump.png");
        }
            break;
        case PowerType::DAD:
        {
            m_icon = Sprite::createWithSpriteFrameName("item_dad.png");
        }
            break;
        case PowerType::LANDBUILD:
        {
            m_icon = Sprite::createWithSpriteFrameName("item_buildland.png");
        }
            break;
        case PowerType::FLY:
        {
            m_icon = Sprite::createWithSpriteFrameName("item_fly.png");
        }
            break;
        case PowerType::REBORN:
        {
            m_icon = Sprite::createWithSpriteFrameName("item_reborn.png");
        }
            break;
            
        default:
            break;
    }
    
    m_icon->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(m_icon);
    
    return true;
}

void PowerIcon::setPercentage(float _per)
{
    m_proBg->setPercentage(_per);
}

PowerIcon* PowerIcon::create(PowerType _type)
{
    auto _icon = new PowerIcon();
    if (_icon && _icon->init(_type))
    {
        _icon->autorelease();
        return _icon;
    }
    
    delete _icon;
    _icon = nullptr;
    
    return nullptr;
}