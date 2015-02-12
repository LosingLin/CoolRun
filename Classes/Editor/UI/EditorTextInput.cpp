//
//  EditorTextInput.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/30.
//
//

#include "EditorTextInput.h"
#include "EditorText.h"
#include "MYTextInput.h"


EditorTextInput::EditorTextInput()
: EditorNode()
, m_input(nullptr)
, textInputDone(nullptr)
{
    
}
EditorTextInput::~EditorTextInput()
{
    
}

bool EditorTextInput::init()
{
    if (!EditorNode::init())
    {
        return false;
    }
    
    return true;
}

bool EditorTextInput::init(const string& title, const Size& csize)
{
    if (!this->init())
    {
        return false;
    }
    
    this->setContentSize(csize);
    
    this->setTouchEnable(false);
    
    auto text = EditorText::create(title, Size(100, csize.height), 30);
    text->setTouchEnable(false);
    text->setPosition(Vec2(0, 0));
    this->addChild(text);
    
    m_input = MYTextInput::create(Size(csize.width - 100, csize.height));
    m_input->setPosition(100, 0);
    this->addChild(m_input);
    m_input->textInputDone = CC_CALLBACK_1(EditorTextInput::inputDone, this);
    
    return true;
}

void EditorTextInput::setText(const string& text)
{
    m_input->setText(text.c_str());
}
const char* EditorTextInput::getText()
{
    return m_input->getText();
}

void EditorTextInput::inputDone(const string& text)
{
    log("input is %s\n", text.c_str());
    if (textInputDone)
    {
        textInputDone(text);
    }
}

EditorTextInput* EditorTextInput::create(const string& title, const Size& csize)
{
    auto eti = new EditorTextInput();
    if (eti && eti->init(title, csize))
    {
        eti->autorelease();
        return eti;
    }
    delete eti;
    return nullptr;
}