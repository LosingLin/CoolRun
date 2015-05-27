//
//  EditorCollectionMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/2/7.
//
//

#include "EditorCollectionMenu.h"
#include "EditorUIBase.h"
//#include "PhysicNodeFactory.h"
#include "Collection.h"

EditorCollectionMenu::EditorCollectionMenu()
: EditorMenu()
{
    
}
EditorCollectionMenu::~EditorCollectionMenu()
{
    
}

bool EditorCollectionMenu::init()
{
    if (!EditorMenu::init())
    {
        return false;
    }
    
    this->setMenuType(MenuType::COLLECION);
    
    auto csize = Size(200, 3000);
    this->setContentSize(csize);
    
    this->getTouchListener()->setSwallowTouches(false);
    
    auto layer = LayerColor::create(Color4B(80, 120, 80, 255), csize.width, csize.height);
    this->addChild(layer);
    
    auto size = Size(160, 160);
    int y = csize.height - 180;
    //int len = sizeof(CollectionMatrixInstance::INSTANCE)/sizeof(CollectionMatrixInstance::INSTANCE[0]);
    int len = Collection::getMatrixTotalNum();
    for (int i = 0; i < len; ++ i)
    {
        
        auto obj = EditorPhysicNodeContainer::createBaseCollectionPhysicNode(i);
        auto epnc = EditorPhysicNodeContainer::create(size, obj);
        epnc->setPosition(Vec2(20, y));
        this->addChild(epnc);
        y -= 180;
        epnc->getTouchListener()->setSwallowTouches(false);
        epnc->touchNoneMoveEnded = CC_CALLBACK_0(EditorCollectionMenu::menuCallback, this, i);
    }
    
    return true;
}

void EditorCollectionMenu::menuCallback(int cmIndex)
{
    auto obj = EditorPhysicNodeContainer::createBaseCollectionPhysicNode(cmIndex);
    auto epnc = EditorPhysicNodeContainer::create(obj);
//    epnc->setPhysicNodeType(type);
    auto collection = EditorPhysicNodeContainer::createBaseCollection(cmIndex);
    this->getEditorListener()->addCollection(epnc, collection);
}