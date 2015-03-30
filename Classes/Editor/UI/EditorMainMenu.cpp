//
//  EditorMainMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/28.
//
//

#include "EditorMainMenu.h"
#include "EditorUIBase.h"
#include "EditorItemMenu.h"
#include "EditorOpenFileMenu.h"
#include "EditorPageMenu.h"
#include "MenuScene.h"

EditorMainMenu::EditorMainMenu()
: EditorMenu()
{
    
}

EditorMainMenu::~EditorMainMenu()
{
    
}

bool EditorMainMenu::init()
{
    if (!EditorMenu::init())
    {
        return false;
    }
    
    this->setMenuType(MenuType::MAIN);
    
    auto csize = Size(200, 1000);
    this->setContentSize(csize);
    
    this->getTouchListener()->setSwallowTouches(false);
    
    auto layer = LayerColor::create(Color4B(200, 20, 200, 150), 200, 1000);
    this->addChild(layer);
    
    string texts[] = {"添加物体", "页", "文件", "运行", "退出"};
    auto _size = Size(160, 80);
    int fontSize = 30;
    
    int y = 900;
    for (int i = 0; i < sizeof(texts)/sizeof(texts[0]); ++i)
    {
        auto menuItem = EditorText::create(texts[i], _size, fontSize);
        menuItem->setPosition(Vec2(20, y));
        y -= 100;
        menuItem->touchNoneMoveEnded = CC_CALLBACK_0(EditorMainMenu::menuCallback, this, i);
        this->addChild(menuItem);
    }
    
    
    
    return true;
}

void EditorMainMenu::spaceCallback()
{
    this->getEditorListener()->hideMenu(EditorListener::MenuState::FIRST);
}

void EditorMainMenu::menuCallback(int index)
{
    log("menuCallback %d", index);
    switch (index)
    {
        case 0:
        {
            this->getEditorListener()->showMenu(EditorListener::MenuState::SECOND, EditorItemMenu::create());
        }
            break;
        case 1:
        {
            this->getEditorListener()->showMenu(EditorListener::MenuState::SECOND, EditorPageMenu::create());
        }
            break;
        case 2:
        {
            this->getEditorListener()->showMenu(EditorListener::MenuState::SECOND, EditorOpenFileMenu::create());
        }
            break;
        case 3:
        {
            this->getEditorListener()->run();
        }
            break;
        case 4:
        {
            Director::getInstance()->replaceScene(MenuLayer::createScene());
        }
            break;
            
        default:
            break;
    }
}