//
//  Score.cpp
//  CoolRun
//
//  Created by ManYou on 15/2/11.
//
//

#include "Score.h"

Score::Score()
: Node()
, m_numLab(nullptr)
{
    
}
Score::~Score()
{
    
}

bool Score::init()
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
    
    auto scoreTxt = Label::createWithSystemFont("Score:", "", 30);
    scoreTxt->setAnchorPoint(Vec2(0, 0.5));
    scoreTxt->setPosition(Vec2(20, csize.height/2));
    this->addChild(scoreTxt);
    
    m_numLab = Label::createWithSystemFont("0", "", 30);
    m_numLab->setAnchorPoint(Vec2(0, 0.5));
    m_numLab->setTextColor(Color4B::GREEN);
    m_numLab->setPosition(Vec2(110, csize.height/2));
    m_numLab->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
    this->addChild(m_numLab);
    return true;
}

void Score::setString(const std::string& str)
{
    m_numLab->setString(str);
}