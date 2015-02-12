//
//  Stretch.cpp
//  CoolRun
//
//  Created by ManYou on 15/2/11.
//
//

#include "Stretch.h"

Stretch::Stretch()
: Node()
, m_numLab(nullptr)
{
    
}
Stretch::~Stretch()
{
    
}

bool Stretch::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    auto csize = Size(260, 54);
    this->setContentSize(csize);
    
    auto bg = Scale9Sprite::createWithSpriteFrameName("num_bg.png");
    bg->setPreferredSize(csize);
    bg->setAnchorPoint(Vec2::ZERO);
    this->addChild(bg);
    
    auto StretchTxt = Label::createWithSystemFont("m", "", 32);
    StretchTxt->setAnchorPoint(Vec2(1, 0.5));
    StretchTxt->setPosition(Vec2(csize.width - 20, csize.height/2));
    this->addChild(StretchTxt);
    
    m_numLab = Label::createWithSystemFont("0", "", 30);
    m_numLab->setAnchorPoint(Vec2(1, 0.5));
    m_numLab->setTextColor(Color4B::YELLOW);
    m_numLab->setPosition(Vec2(csize.width - 52, csize.height/2));
    m_numLab->setAlignment(TextHAlignment::RIGHT, TextVAlignment::CENTER);
    this->addChild(m_numLab);
    return true;
}

void Stretch::setString(const std::string& str)
{
    m_numLab->setString(str);
}