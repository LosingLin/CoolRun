//
//  EditorPageMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/3/27.
//
//

#include "EditorPageMenu.h"
#include "EditorUIBase.h"

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
    
    auto csize = Size(200, 1000);
    this->setContentSize(csize);
    
    this->getTouchListener()->setSwallowTouches(false);
    
    
    
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
    else if(index == pageNum)
    {
        this->getEditorListener()->addPage();
        this->updatePage();
    }
    else if(index == pageNum + 1)
    {
        b_isEditing = !b_isEditing;
        this->updatePage();
    }
}

void EditorPageMenu::spaceCallback()
{
    this->getEditorListener()->hideMenu(EditorListener::MenuState::SECOND);
}

void EditorPageMenu::updatePage()
{
    this->removeAllChildrenWithCleanup(true);
    
    auto pageNum = this->getEditorListener()->pageNumber();
    
    auto _size = Size(160, 80);
    int fontSize = 30;
    
    int y = 900;
    for (int i = 0; i < pageNum + 2; ++i)
    {
        auto str = string();
        
        if (b_isEditing)
        {
            str = "-";
            if (i == pageNum)
            {
                str = "+";
            }
            else if (i == pageNum + 1)
            {
                str = "返回";
            }
        }
        else
        {
            auto ss = stringstream();
            ss << "第";
            ss << i+1;
            ss << "页";
            ss >> str;
            if (i == pageNum)
            {
                str = "+";
            }
            else if (i == pageNum + 1)
            {
                str = "编辑";
            }
        }
        
        auto menuItem = EditorText::create(str, _size, fontSize);
        menuItem->setPosition(Vec2(20, y));
        y -= 100;
        menuItem->touchNoneMoveEnded = CC_CALLBACK_0(EditorPageMenu::menuCallback, this, i);
        this->addChild(menuItem);
    }
    
}