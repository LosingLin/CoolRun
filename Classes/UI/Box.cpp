//
//  Box.cpp
//  CoolRun
//
//  Created by ManYou on 15/6/24.
//
//

#include "Box.h"
#include "MYMultiLanguageManager.h"
#include "ResourceManager.h"

Box::Box()
: Node()
, m_numLab(nullptr)
{
    
}
Box::~Box()
{
    
}

bool Box::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    auto csize = Size(320, 54);
    this->setContentSize(csize);
    
    auto bg = Scale9Sprite::createWithSpriteFrameName("num_bg.png");
    bg->setPreferredSize(csize);
    bg->setAnchorPoint(Vec2::ZERO);
    this->addChild(bg);
    
//    auto box_icon = Sprite::createWithSpriteFrameName("");
//    box_icon->setPosition(Vec2(12, 2));
//    this->addChild(box_icon);
    
    m_numLab = Label::createWithBMFont(ResourceManager::getInstance()->getFntRes("Score"), "0");
    m_numLab->setAnchorPoint(Vec2(0, 0.5));
    m_numLab->setPosition(Vec2(120, 20));
    m_numLab->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
    this->addChild(m_numLab);
    return true;
}

void Box::setString(const std::string& str)
{
    auto _scaleTo = ScaleTo::create(0.1f, 1.2f);
    auto _scaleTo2 = ScaleTo::create(0.1f, 1.0f);
    m_numLab->runAction(Sequence::create(_scaleTo, _scaleTo2, NULL));
    m_numLab->setString(str);
}