//
//  EditorItemObjectMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/12.
//
//

#include "EditorItemObjectMenu.h"
#include "EditorUIBase.h"
#include "PhysicNodeFactory.h"

EditorItemObjectMenu::EditorItemObjectMenu()
: EditorMenu()
{
    
}
EditorItemObjectMenu::~EditorItemObjectMenu()
{
    
}

bool EditorItemObjectMenu::init()
{
    if (!EditorMenu::init())
    {
        return false;
    }
    
    this->setMenuType(MenuType::ITEMOBJECT);
    
    auto csize = Size(200, 3000);
    this->setContentSize(csize);
    
    this->getTouchListener()->setSwallowTouches(false);
    
    auto layer = LayerColor::create(Color4B(200, 200, 20, 150), csize.width, csize.height);
    this->addChild(layer);
    
    auto size = Size(160, 160);
    int y = csize.height - 180;
    for (int i = 1; i < kPhysicNodeTypeCount; ++ i)
    {
        if (i == kPhysicNodeSpider || i == kPhysicNodeEnemy || i == kPhysicNodeItem || i == kPhysicNodeBulletPoison || i == kPhysicNodeCoin || i == kPhysicNodeBulletAlertNet || i == kPhysicNodeBulletAlertPoison || i == kPhysicNodeSaw || i == kPhysicNodeSpiderFly || i == kPhysicNodeSpiderKind || i == kPhysicNodeSpiderPoison || i == kPhysicNodeSpiderSpines || i == kPhysicNodeStone)
        {
            continue;
        }
        auto obj = EditorPhysicNodeContainer::createBasePhysicNode((PhysicNodeType)i);
        auto epnc = EditorPhysicNodeContainer::create(size, obj);
        epnc->setPosition(Vec2(20, y));
        this->addChild(epnc);
        y -= 180;
        epnc->getTouchListener()->setSwallowTouches(false);
        epnc->touchNoneMoveEnded = CC_CALLBACK_0(EditorItemObjectMenu::menuCallback, this, (PhysicNodeType)i);
    }
    
    return true;
}

void EditorItemObjectMenu::menuCallback(PhysicNodeType type)
{
    auto obj = EditorPhysicNodeContainer::createBasePhysicNode(type);
    auto epnc = EditorPhysicNodeContainer::create(obj);
    epnc->setPhysicNodeType(type);
    epnc->getTouchListener()->setSwallowTouches(true);
    this->getEditorListener()->addObject(epnc);
}