//
//  EditorText.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/29.
//
//

#include "EditorText.h"

EditorText::EditorText()
: EditorNode()
, m_label(nullptr)
{
    
}
EditorText::~EditorText()
{
    
}

bool EditorText::init()
{
    if (!EditorNode::init())
    {
        return false;
    }
    
    
    return true;
}

bool EditorText::init(const string& text, const Size& csize, int fontSize)
{
    if (!this->init())
    {
        return false;
    }
    
    this->setContentSize(csize);
    
    auto bg = Scale9Sprite::createWithSpriteFrameName("editorFrame_bg.png");
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPreferredSize(csize);
    this->addChild(bg);
    
    m_label = Label::createWithSystemFont(text, "", fontSize);
    m_label->setHorizontalAlignment(TextHAlignment::CENTER);
    m_label->setVerticalAlignment(TextVAlignment::CENTER);
    m_label->setAnchorPoint(Vec2(0.5, 0.5));
    m_label->setPosition(Vec2(csize.width * 0.5, csize.height * 0.5));
    m_label->setColor(Color3B::BLACK);
    this->addChild(m_label);
    
    return true;
}

void EditorText::setText(const string& text)
{
    m_label->setString(text);
}
const string EditorText::getText()
{
    return m_label->getString();
}

EditorText* EditorText::create(const string& text, const Size& csize, int fontSize)
{
    auto etext = new EditorText();
    if (etext && etext->init(text, csize, fontSize))
    {
        etext->autorelease();
        return etext;
    }
    delete etext;
    return nullptr;
}