//
//  EditorItemMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/29.
//
//

#include "EditorItemMenu.h"
#include "EditorText.h"
#include "EditorObjectMenu.h"
#include "EditorCollectionMenu.h"

EditorItemMenu::EditorItemMenu()
: EditorMenu()
{
    
}
EditorItemMenu::~EditorItemMenu()
{
    
}

bool EditorItemMenu::init()
{
    if (!EditorMenu::init())
    {
        return false;
    }
    
    this->setMenuType(MenuType::ITEM);
    
    auto csize = Size(200, 1000);
    this->setContentSize(csize);
    
    this->getTouchListener()->setSwallowTouches(false);
    
    auto layer = LayerColor::create(Color4B(200, 20, 200, 150), 200, 1000);
    this->addChild(layer);
    
    string texts[] = {"普通物体", "集合", "清空"};
    auto _size = Size(160, 80);
    int fontSize = 30;
    
    int y = 900;
    for (int i = 0; i < sizeof(texts)/sizeof(texts[0]); ++i)
    {
        auto menuItem = EditorText::create(texts[i], _size, fontSize);
        menuItem->setPosition(Vec2(20, y));
        y -= 100;
        menuItem->touchNoneMoveEnded = CC_CALLBACK_0(EditorItemMenu::menuCallback, this, i);
        this->addChild(menuItem);
    }
    
    
    return true;
}

void EditorItemMenu::menuCallback(int index)
{
    log("menuCallback %d", index);
    switch (index)
    {
        case 0:
        {
            this->getEditorListener()->showMenu(EditorListener::MenuState::THIRD, EditorObjectMenu::create());
        }
            break;
        case 1:
        {
            this->getEditorListener()->showMenu(EditorListener::MenuState::THIRD, EditorCollectionMenu::create());
        }
            break;
        case 2:
        {
            this->getEditorListener()->clearUpCurrentPage();
        }
            break;
            
        default:
            break;
    }
}

void EditorItemMenu::spaceCallback()
{
    this->getEditorListener()->hideMenu(EditorListener::MenuState::THIRD);
}