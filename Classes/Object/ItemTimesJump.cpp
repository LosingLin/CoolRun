//
//  ItemTimesJump.cpp
//  CoolRun
//
//  Created by ManYou on 14/12/24.
//
//

#include "ItemTimesJump.h"
#include "Runner.h"

ItemTimesJump::ItemTimesJump()
: Item()
{
}
ItemTimesJump::~ItemTimesJump()
{
}


bool ItemTimesJump::init()
{
    if (!Item::init())
    {
        return false;
    }
    auto csize = this->getContentSize();
    m_icon = Sprite::createWithSpriteFrameName("item_jump.png");
    m_icon->setPosition(Vec2(csize.width/2, csize.height - 74));
    this->addChild(m_icon);
    
    return true;
}

void ItemTimesJump::active(Runner *runner)
{
    this->setDestoryed(true);
    //log("....active...");
    runner->startTimesJump();
//    runner->startMagnet();
//    runner->startTimesCoin();
//    runner->startLandBuild();
//    runner->startDad();
//    m_gameController->spareRunner(runner);
//    runner->startFly();
}