//
//  EditorPageMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/3/27.
//
//

#include "EditorPageMenu.h"
#include "EditorUIBase.h"
#include "MYMultiLanguageManager.h"

EditorPageMenu::EditorPageMenu()
: EditorMenu()
, b_isEditing(false)
{
    
}
EditorPageMenu::~EditorPageMenu()
{
    
}

bool EditorPageMenu::init()
{
    if (!EditorMenu::init())
    {
        return false;
    }
    
    this->setMenuType(MenuType::PAGE);
    
    auto csize = Size(200, 2000);
    this->setContentSize(csize);
    
    this->getTouchListener()->setSwallowTouches(false);
    
    this->getTouchListener()->setEnabled(false);
    
    
    return true;
}

void EditorPageMenu::onEnter()
{
    EditorMenu::onEnter();
    
    this->updatePage();
}
void EditorPageMenu::onExit()
{
    EditorMenu::onExit();
}

void EditorPageMenu::menuCallback(int index)
{
    auto pageNum = this->getEditorListener()->pageNumber();
    
    int totalPageNum = pageNum + 2;
    if (pageNum >= MAXEDITORPAGE)
    {
        totalPageNum = MAXEDITORPAGE + 1;
    }
    
    if (index < pageNum)
    {
        if (b_isEditing)
        {
            this->getEditorListener()->deletePage(index);
            this->updatePage();
        }
        else
        {
            this->getEditorListener()->showPage(index);
        }
        
    }
    else if(index == totalPageNum - 2)
    {
        this->getEditorListener()->addPage();
        this->updatePage();
    }
    else if(index == totalPageNum - 1)
    {
        b_isEditing = !b_isEditing;
        this->updatePage();
    }
}

void EditorPageMenu::spaceCallback()
{
    //this->getEditorListener()->hideMenu(EditorListener::MenuState::SECOND);
}

void EditorPageMenu::updatePage()
{
    this->removeAllChildrenWithCleanup(true);
    
    auto csize = this->getContentSize();
    auto layer = LayerColor::create(Color4B(100, 20, 140, 255), csize.width, csize.height);
    this->addChild(layer);
    
    auto pageNum = this->getEditorListener()->pageNumber();
    auto _size = Size(160, 80);
    int fontSize = 30;
    
    int y = csize.height-100;
    int totalPageNum = pageNum + 2;
    if (pageNum >= MAXEDITORPAGE)
    {
        totalPageNum = MAXEDITORPAGE + 1;
    }
    for (int i = 0; i < totalPageNum; ++i)
    {
        auto str = string();
        
        if (b_isEditing)
        {
            str = "-";
            if (i == pageNum)
            {
                str = "+";
            }
            if (i == totalPageNum - 1)
            {
                str = MYMultiLanguageManager::getInstance()->getText("e_back");
            }
        }
        else
        {
            auto ss = stringstream();
            ss << MYMultiLanguageManager::getInstance()->getText("e_indexStart");
            ss << i+1;
            ss << MYMultiLanguageManager::getInstance()->getText("e_indexEnd");
            ss >> str;
            if (i == pageNum)
            {
                str = "+";
            }
            if (i == totalPageNum - 1)
            {
                str = MYMultiLanguageManager::getInstance()->getText("e_edit");
            }
        }
        
        auto menuItem = EditorText::create(str, _size, fontSize);
        menuItem->setPosition(Vec2(20, y));
        y -= 100;
        menuItem->touchNoneMoveEnded = CC_CALLBACK_0(EditorPageMenu::menuCallback, this, i);
        menuItem->getTouchListener()->setSwallowTouches(false);
        this->addChild(menuItem);
    }
    
}