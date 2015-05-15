//
//  EditorObjectMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/29.
//
//

#include "EditorObjectMenu.h"
#include "EditorUIBase.h"
#include "PhysicNodeFactory.h"

EditorObjectMenu::EditorObjectMenu()
: EditorMenu()
{
    
}
EditorObjectMenu::~EditorObjectMenu()
{
    
}

bool EditorObjectMenu::init()
{
    if (!EditorMenu::init())
    {
        return false;
    }
    
    this->setMenuType(MenuType::OBJECT);
    
    auto csize = Size(200, 3000);
    this->setContentSize(csize);
    
    this->getTouchListener()->setSwallowTouches(false);
    
    auto layer = LayerColor::create(Color4B(200, 200, 20, 150), csize.width, csize.height);
    this->addChild(layer);
    
    auto size = Size(160, 160);
    int y = csize.height - 180;
    for (int i = 1; i < kPhysicNodeTypeCount; ++ i)
    {
        if (i == kPhysicNodeSpider || i == kPhysicNodeEnemy || i == kPhysicNodeItem || i == kPhysicNodeBulletPoison || i == kPhysicNodeCoin || i == kPhysicNodeItemDad || i == kPhysicNodeItemFly ||  i == kPhysicNodeItemLandBuild || i == kPhysicNodeItemMagnet || i == kPhysicNodeItemSpare || i == kPhysicNodeItemTimesCoin || i == kPhysicNodeItemTimesJump)
        {
            continue;
        }
        auto obj = EditorPhysicNodeContainer::createBasePhysicNode((PhysicNodeType)i);
        auto epnc = EditorPhysicNodeContainer::create(size, obj);
        epnc->setPosition(Vec2(20, y));
        this->addChild(epnc);
        y -= 180;
        epnc->getTouchListener()->setSwallowTouches(false);
        epnc->touchNoneMoveEnded = CC_CALLBACK_0(EditorObjectMenu::menuCallback, this, (PhysicNodeType)i);
    }
    
    return true;
}

void EditorObjectMenu::menuCallback(PhysicNodeType type)
{
    auto obj = EditorPhysicNodeContainer::createBasePhysicNode(type);
    auto epnc = EditorPhysicNodeContainer::create(obj);
    epnc->setPhysicNodeType(type);
    epnc->getTouchListener()->setSwallowTouches(true);
    this->getEditorListener()->addObject(epnc);
}