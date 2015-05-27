//
//  PowerIconBar.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/25.
//
//

#include "PowerIconBar.h"
#include "GlobalDefined.h"

PowerIconBar::PowerIconBar()
: Node()
, m_icons(nullptr)
{
    
}
PowerIconBar::~PowerIconBar()
{
    CC_SAFE_RELEASE_NULL(m_icons);
}

bool PowerIconBar::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    CREATEANDRETAINARRAY(m_icons);
    
    auto tempIcon = PowerIcon::create(PowerIcon::PowerType::MAGNET);
    auto isize = tempIcon->getContentSize();
    this->setContentSize(Size(isize.width * 8, isize.height));
    
//    auto layer = LayerColor::create(Color4B(100, 20, 100, 255), isize.width * 8, isize.height);
//    this->addChild(layer);
    
    return true;
}

void PowerIconBar::addPowerIcon(PowerIcon::PowerType _type)
{
    auto icon = this->getPowerIcon(_type);
    if (icon)
    {
        icon->setPercentage(1.0f);
    }
    else
    {
        icon = PowerIcon::create(_type);
        icon->setAnchorPoint(Vec2(0.5, 0.5));
        this->addChild(icon);
        m_icons->addObject(icon);
    }
    this->layoutIcons();
}
void PowerIconBar::removePowerIcon(PowerIcon::PowerType _type)
{
    auto icon = this->getPowerIcon(_type);
    if (icon)
    {
        icon->removeFromParentAndCleanup(true);
        m_icons->removeObject(icon);
    }
    this->layoutIcons();
}
void PowerIconBar::updatePowerIcon(PowerIcon::PowerType _type, float _persentage)
{
    auto icon = this->getPowerIcon(_type);
    if (icon)
    {
        icon->setPercentage(_persentage);
    }
}
void PowerIconBar::removeAllPowerIcon()
{
    for (int i = 0; i < m_icons->count(); ++ i)
    {
        auto _icon = dynamic_cast<PowerIcon*>(m_icons->getObjectAtIndex(i));
        _icon->removeFromParentAndCleanup(true);
    }
    m_icons->removeAllObjects();
}

void PowerIconBar::layoutIcons()
{
    auto csize = this->getContentSize();
    
    for (int i = 0; i < m_icons->count(); ++ i)
    {
        auto _icon = dynamic_cast<PowerIcon*>(m_icons->getObjectAtIndex(i));
        auto isize = _icon->getContentSize();
        int half = (int)m_icons->count()/2;
        auto pos = Vec2(csize.width/2, csize.height/2);
        pos.x += (i - half) * isize.width;
        
        if ((int)m_icons->count()%2 == 0)
        {
            pos.x += isize.width/2;
        }
        _icon->setPosition(pos);
    }
}

PowerIcon* PowerIconBar::getPowerIcon(PowerIcon::PowerType _type)
{
    for (int i = 0; i < m_icons->count(); ++ i)
    {
        auto _icon = dynamic_cast<PowerIcon*>(m_icons->getObjectAtIndex(i));
        if (_type == _icon->getPowerType())
        {
            return _icon;
        }
    }
    
    return nullptr;
}