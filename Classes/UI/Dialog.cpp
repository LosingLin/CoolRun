//
//  Dialog.cpp
//  CoolRun
//
//  Created by ManYou on 14-9-9.
//
//

#include "Dialog.h"

Dialog::Dialog()
: Node()
, m_label(nullptr)
{
}
Dialog::~Dialog()
{
}
bool Dialog::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    auto _bg = Sprite::createWithSpriteFrameName("dialog_bg.png");
    auto csize = _bg->getContentSize();
    this->setContentSize(csize);
    _bg->setPosition(Vec2(csize.width/2, csize.height/2));
    this->addChild(_bg);
    
    m_label = LabelTTF::create("", "", 25);
    m_label->setColor(Color3B(0, 0, 0));
    m_label->setDimensions(Size(280, 110));
    m_label->setHorizontalAlignment(TextHAlignment::LEFT);
    m_label->setVerticalAlignment(TextVAlignment::TOP);
    m_label->setAnchorPoint(Vec2(0, 1));
    m_label->setPosition(Vec2(4, csize.height-18));
    this->addChild(m_label, 2);
    
    
    return true;
}

void Dialog::say(const string& words)
{
    CCASSERT(m_label, "label is not exist");
    log("words : %s", words.c_str());
    m_label->setString(words);
}