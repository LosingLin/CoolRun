//
//  EditorOpenFileMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/2/4.
//
//

#include "EditorOpenFileMenu.h"
#include "EditorUIBase.h"

EditorOpenFileMenu::EditorOpenFileMenu()
: EditorMenu()
, m_open(nullptr)
, m_save(nullptr)
, m_path(nullptr)
{
    
}
EditorOpenFileMenu::~EditorOpenFileMenu()
{
    
}

bool EditorOpenFileMenu::init()
{
    if (!EditorMenu::init())
    {
        return false;
    }
    
    this->setMenuType(EditorMenu::MenuType::OPENFILE);
    
    auto csize = Size(800, 1000);
    this->setContentSize(csize);
    
    this->getTouchListener()->setSwallowTouches(false);
    
    auto layer = LayerColor::create(Color4B(20, 20, 200, 150), csize.width, csize.height);
    this->addChild(layer);
    
    int y = csize.height - 200;
    m_path = EditorTextInput::create("path", Size(csize.width - 100, 100));
    m_path->setPosition(Vec2(50, y));
    this->addChild(m_path);
    y -= 120;
    
    m_open = EditorText::create("Open", Size(csize.width - 200, 100), 30);
    m_open->setPosition(Vec2(100, y));
    m_open->touchNoneMoveEnded = CC_CALLBACK_0(EditorOpenFileMenu::open, this);
    this->addChild(m_open);
    y -= 120;
    
    m_save = EditorText::create("Save", Size(csize.width - 200, 100), 30);
    m_save->setPosition(Vec2(100, y));
    m_save->touchNoneMoveEnded = CC_CALLBACK_0(EditorOpenFileMenu::save, this);
    this->addChild(m_save);
    y -= 120;
    
    return true;
}

void EditorOpenFileMenu::open()
{
    auto filePath = m_path->getText();
    this->getEditorListener()->openFile(filePath);
    
}
void EditorOpenFileMenu::save()
{
    auto filePath = m_path->getText();
    this->getEditorListener()->save(filePath);
}