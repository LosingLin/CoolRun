//
//  ItemLandBuild.cpp
//  CoolRun
//
//  Created by ManYou on 14/12/31.
//
//

#include "ItemLandBuild.h"
#include "Runner.h"

ItemLandBuild::ItemLandBuild()
: Item()
{
}
ItemLandBuild::~ItemLandBuild()
{
}


bool ItemLandBuild::init()
{
    if (!Item::init())
    {
        return false;
    }
    auto csize = this->getContentSize();
    m_icon = Sprite::createWithSpriteFrameName("item_buildland.png");
    m_icon->setPosition(Vec2(csize.width/2, csize.height - 74));
    this->addChild(m_icon);
    
    m_icon->setScale(0.9f);
    return true;
}

void ItemLandBuild::active(Runner *runner)
{
    this->setDestoryed(true);
    //log("....active...");
    
    runner->startLandBuild();
}