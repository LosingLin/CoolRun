//
//  ItemMagnet.cpp
//  CoolRun
//
//  Created by ManYou on 14/12/23.
//
//

#include "ItemMagnet.h"
#include "Runner.h"

ItemMagnet::ItemMagnet()
: Item()
{
}
ItemMagnet::~ItemMagnet()
{
}


bool ItemMagnet::init()
{
    if (!Item::init())
    {
        return false;
    }
    auto csize = this->getContentSize();
    m_icon = Sprite::createWithSpriteFrameName("item_mag.png");
    m_icon->setPosition(Vec2(csize.width/2, csize.height - 74));
    this->addChild(m_icon);
    
    return true;
}

void ItemMagnet::active(Runner *runner)
{
    this->setDestoryed(true);
    //log("....active...");
    runner->startMagnet();
}