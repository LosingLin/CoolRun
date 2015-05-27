//
//  EditorMenu.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/29.
//
//

#include "EditorMenu.h"

EditorMenu::EditorMenu()
: EditorNode()
, m_type(MenuType::NONE)
{
    
}
EditorMenu::~EditorMenu()
{
    
}

bool EditorMenu::init()
{
    if (!EditorNode::init())
    {
        return false;
    }
    
    this->getTouchListener()->setEnabled(false);
    this->touchNoneMoveEnded = CC_CALLBACK_0(EditorMenu::spaceCallback, this);
    
    return true;
}