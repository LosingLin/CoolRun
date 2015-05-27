//
//  ItemDad.cpp
//  CoolRun
//
//  Created by ManYou on 14/12/25.
//
//

#include "ItemDad.h"
#include "Runner.h"

ItemDad::ItemDad()
: Item()
{
}
ItemDad::~ItemDad()
{
}


bool ItemDad::init()
{
    if (!Item::init())
    {
        return false;
    }
    auto csize = this->getContentSize();
    m_icon = Sprite::createWithSpriteFrameName("item_dad.png");
    m_icon->setPosition(Vec2(csize.width/2, csize.height - 74));
    this->addChild(m_icon);
    
    m_icon->setScale(0.9f);
    return true;
}

void ItemDad::active(Runner *runner)
{
    this->setDestoryed(true);
    //log("....active...");
    runner->startDad();
}
