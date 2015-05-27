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
#include "SceneHelp.h"
#include "EditorManager.h"
#include "MYMultiLanguageManager.h"

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
    
    auto layer = LayerColor::create(Color4B(100, 20, 100, 255), 200, 1000);
    this->addChild(layer);
    
    EditorManager::EditorType _type = EditorManager::getInstance()->getEditorType();
    
    string texts[] = {
        MYMultiLanguageManager::getInstance()->getText("e_add"),
        MYMultiLanguageManager::getInstance()->getText("e_pages"),
        MYMultiLanguageManager::getInstance()->getText("e_save"),
        MYMultiLanguageManager::getInstance()->getText("e_run"),
        MYMultiLanguageManager::getInstance()->getText("e_exit")};
    if (EditorManager::EditorType::PLAYER == _type)
    {
        texts[2] = MYMultiLanguageManager::getInstance()->getText("e_save");
    }
    else if(EditorManager::EditorType::DEVELOPER == _type)
    {
        texts[2] = MYMultiLanguageManager::getInstance()->getText("e_file");
    }
    
    auto _size = Size(160, 80);
    int fontSize = 30;
    
    int y = 900;
    for (int i = 0; i < sizeof(texts)/sizeof(texts[0]); ++i)
    {
        auto menuItem = EditorText::create(texts[i], _size, fontSize);
        menuItem->setPosition(Vec2(20, y));
        y -= 100;
        menuItem->touchNoneMoveEnded = CC_CALLBACK_0(EditorMainMenu::menuCallback, this, i);
        menuItem->getTouchListener()->setSwallowTouches(false);
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
    //log("menuCallback %d", index);
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
            EditorManager::EditorType _type = EditorManager::getInstance()->getEditorType();
            if (EditorManager::EditorType::PLAYER == _type)
            {
                this->getEditorListener()->save("");
            }
            else if(EditorManager::EditorType::DEVELOPER == _type)
            {
                this->getEditorListener()->showMenu(EditorListener::MenuState::SECOND, EditorOpenFileMenu::create());
            }
        }
            break;
        case 3:
        {
            this->getEditorListener()->run();
        }
            break;
        case 4:
        {
            SceneHelp::replaceScene(MenuLayer::createScene());
        }
            break;
            
        default:
            break;
    }
}