//
//  ItemTimesCoin.cpp
//  CoolRun
//
//  Created by ManYou on 14/12/24.
//
//

#include "ItemTimesCoin.h"
#include "Runner.h"

ItemTimesCoin::ItemTimesCoin()
: Item()
{
}
ItemTimesCoin::~ItemTimesCoin()
{
}


bool ItemTimesCoin::init()
{
    if (!Item::init())
    {
        return false;
    }
    auto csize = this->getContentSize();
    m_icon = Sprite::createWithSpriteFrameName("item_timecoin.png");
    m_icon->setPosition(Vec2(csize.width/2, csize.height - 74));
    this->addChild(m_icon);
    
    m_icon->setScale(0.9f);
    return true;
}

void ItemTimesCoin::active(Runner *runner)
{
    this->setDestoryed(true);
    //log("....active...");
    runner->startTimesCoin();
}