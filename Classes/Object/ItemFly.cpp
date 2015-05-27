//
//  ItemFly.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/1.
//
//

#include "ItemFly.h"
#include "Runner.h"

ItemFly::ItemFly()
: Item()
{
}
ItemFly::~ItemFly()
{
}


bool ItemFly::init()
{
    if (!Item::init())
    {
        return false;
    }
    auto csize = this->getContentSize();
    m_icon = Sprite::createWithSpriteFrameName("item_fly.png");
    m_icon->setPosition(Vec2(csize.width/2, csize.height - 74));
    this->addChild(m_icon);
    
    m_icon->setScale(0.9f);
    return true;
}

void ItemFly::active(Runner *runner)
{
    this->setDestoryed(true);
    //log("....active...");
    
    runner->startFly();
}