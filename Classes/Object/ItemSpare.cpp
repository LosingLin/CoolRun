//
//  ItemSpare.cpp
//  CoolRun
//
//  Created by ManYou on 14/12/23.
//
//

#include "ItemSpare.h"
#include "Runner.h"

ItemSpare::ItemSpare()
: Item()
{
}
ItemSpare::~ItemSpare()
{
}


bool ItemSpare::init()
{
    if (!Item::init())
    {
        return false;
    }
    auto csize = this->getContentSize();
    m_icon = Sprite::createWithSpriteFrameName("item_spare.png");
    m_icon->setPosition(Vec2(csize.width/2, csize.height - 74));
    this->addChild(m_icon);
    
    return true;
}

void ItemSpare::active(Runner *runner)
{
    this->setDestoryed(true);
    //log("....active...");
    m_gameController->spareRunner(runner);
}